Scm_GetServByName(const char *name, const char *proto)
{
#if defined(GETSERVBYNAME_R_NUMARGS)
    ScmObj entry = SCM_FALSE;
    {
        int bufsiz = DATA_BUFSIZ;
        struct servent se;
        char staticbuf[DATA_BUFSIZ], *buf = staticbuf;

        for (;;) {
#if GETSERVBYNAME_R_NUMARGS == 5
            if (getservbyname_r(name, proto, &se, buf, bufsiz) != NULL) break;
            if (errno != ERANGE) return SCM_FALSE;
            bufsiz *= 2;
            buf = SCM_NEW_ATOMIC2(char*, bufsiz);
#elif GETSERVBYNAME_R_NUMARGS == 6
            struct servent *rse;
            getservbyname_r(name, proto, &se, buf, bufsiz, &rse);
            if (rse != 0) break;
            else if (errno != ERANGE) return SCM_FALSE;
            bufsiz *= 2;
            buf = SCM_NEW_ATOMIC2(char*, bufsiz);
#else
#error unsupported getservbyname_r variant (configuration error?)
#endif
        }
        entry = SCM_OBJ(make_servent(&se));
    }
    return entry;
#else
    volatile ScmObj entry = SCM_FALSE;
    WITH_GLOBAL_LOCK(netdb_data.servent_mutex,
                     do {
                         struct servent *se = getservbyname(name, proto);
                         if (se != NULL) entry = SCM_OBJ(make_servent(se));
                     } while (0));
    return entry;
#endif
}
