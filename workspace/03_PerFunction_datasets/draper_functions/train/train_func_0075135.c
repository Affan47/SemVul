send_user(USER * user, int tag, char *fmt, ...)
{
    int     len, offset;
    va_list ap;

    if(user->local)
    {

        va_start(ap, fmt);
        vsnprintf(Buf + 4, sizeof(Buf) - 4, fmt, ap);
        va_end(ap);
        set_tag(Buf, tag);
        len = strlen(Buf + 4);
        set_len(Buf, len);
    }
    else
    {

        snprintf(Buf + 4, sizeof(Buf) - 4, ":%s %s ", global.serverName, user->nick);
        offset = strlen(Buf + 4);
        set_tag(Buf, MSG_SERVER_ENCAPSULATED);
        va_start(ap, fmt);
        vsnprintf(Buf + 8 + offset, sizeof(Buf) - 8 - offset, fmt, ap);
        va_end(ap);
        set_tag(Buf + 4 + offset, tag);
        len = strlen(Buf + 8 + offset);
        set_len(Buf + 4 + offset, len);
        len += offset + 4;
        set_len(Buf, len);
    }
    queue_data(user->con, Buf, len + 4);
}
