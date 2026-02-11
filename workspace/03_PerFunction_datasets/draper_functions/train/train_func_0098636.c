kill_user_internal(CONNECTION * con, USER * user, const char *sender_name, USER * sender, const char *fmt, ...)
{
    va_list ap;
    char    reason[128], real_reason[128];

    ASSERT(global.maxReason <= (int) sizeof(reason));
    va_start(ap, fmt);
    vsnprintf(reason, sizeof(reason), fmt, ap);
    va_end(ap);

    pass_message_args(con, MSG_CLIENT_KILL, ":%s %s \"%s\"", sender_name, user->nick, reason);


    if(strncmp("ghost", reason, 5) && strncmp("share", reason, 5))
    {
        notify_mods(KILLLOG_MODE, "%s%s killed %s: %s", !sender ? "Server " : "", sender_name, user->nick, reason);
    }


    if(ISUSER(user->con))
    {
        const char *who;

        if(sender && sender->cloaked && user->level < LEVEL_MODERATOR)
            who = "Operator";
        else
            who = sender_name;
        snprintf(real_reason, sizeof(real_reason), "You have been killed by%s %s: %s", (!sender ? " server" : ""), who, reason);
        zap_local_user(user->con, real_reason);
    }
    else
    {

        hash_remove(global.usersHash, user->nick);
    }
}
