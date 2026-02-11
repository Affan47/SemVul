get_connect(const char *name)
{
    struct connect *conn;
    size_t ii, nlen;


    nlen = strlen(name);
    for (conn = connects; conn; conn = conn->next)
    {
        for (ii = 0; tolower(name[ii]) == tolower(conn->name[ii]) && ii < nlen; ++ii) ;
        if (conn->name[ii] == '\0' && name[ii] == '\0')
            break;
    }


    if (!conn)
    {
        conn = calloc(1, sizeof(*conn) + nlen);
        for (ii = 0; ii < nlen; ++ii)
            conn->name[ii] = name[ii];
        conn->next = connects;
        connects = conn;
    }


    return conn;
}
