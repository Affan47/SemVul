aio_cmd_recvfrom(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
    AioFile *af = Jim_CmdPrivData(interp);
    char *buf;
    union sockaddr_any sa;
    long len;
    socklen_t salen = sizeof(sa);
    int rlen;

    if (Jim_GetLong(interp, argv[0], &len) != JIM_OK) {
        return JIM_ERR;
    }

    buf = Jim_Alloc(len + 1);

    rlen = recvfrom(fileno(af->fp), buf, len, 0, &sa.sa, &salen);
    if (rlen < 0) {
        Jim_Free(buf);
        JimAioSetError(interp, NULL);
        return JIM_ERR;
    }
    buf[rlen] = 0;
    Jim_SetResult(interp, Jim_NewStringObjNoAlloc(interp, buf, rlen));

    if (argc > 1) {

        char addrbuf[60];

#if IPV6
        if (sa.sa.sa_family == PF_INET6) {
            addrbuf[0] = '[';

            inet_ntop(sa.sa.sa_family, &sa.sin6.sin6_addr, addrbuf + 1, sizeof(addrbuf) - 9);
            snprintf(addrbuf + strlen(addrbuf), 8, "]:%d", ntohs(sa.sin.sin_port));
        }
        else
#endif
        {

            inet_ntop(sa.sa.sa_family, &sa.sin.sin_addr, addrbuf, sizeof(addrbuf) - 7);
            snprintf(addrbuf + strlen(addrbuf), 7, ":%d", ntohs(sa.sin.sin_port));
        }

        if (Jim_SetVariable(interp, argv[1], Jim_NewStringObj(interp, addrbuf, -1)) != JIM_OK) {
            return JIM_ERR;
        }
    }

    return JIM_OK;
}
