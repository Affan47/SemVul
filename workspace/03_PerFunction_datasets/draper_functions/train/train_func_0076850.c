drop_privileges()
{
    char* t;
    struct passwd* pw;
    uid_t uid;

    if(g_state.user)
    {
        if(geteuid() != 0)
        {
            sp_messagex(NULL, LOG_WARNING, "must be started as root to switch to user: %s", g_state.user);
            return;
        }

        uid = strtol(g_state.user, &t, 10);
        if(!t[0])
            pw = getpwuid(uid);
        else
            pw = getpwnam(g_state.user);

        if(pw == NULL)
            errx(1, "couldn't look up user: %s", g_state.user);

        if(setgid(pw->pw_gid) == -1 ||
           setuid(pw->pw_uid) == -1)
            err(1, "unable to switch to user: %s (uid %d, gid %d)", g_state.user, pw->pw_uid, pw->pw_gid);


        if(setreuid(-1, 0) == 0)
            err(1, "unable to completely drop privileges");

        sp_messagex(NULL, LOG_DEBUG, "switched to user %s (uid %d, gid %d)", g_state.user, pw->pw_uid, pw->pw_gid);
    }

    if(geteuid() == 0)
        sp_messagex(NULL, LOG_WARNING, "running as root is NOT recommended");
}
