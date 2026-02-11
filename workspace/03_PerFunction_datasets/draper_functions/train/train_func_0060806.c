emitTTYSessG(STRUCTUTMP *ut, struct display *d ATTR_UNUSED, void *ctx ATTR_UNUSED)
{
    gSendStrN(ut->ut_line, sizeof(ut->ut_line));
    gSendStrN(ut->ut_host, sizeof(ut->ut_host));
#ifdef HAVE_VTS
    gSendInt(TTYtoVT(ut->ut_line));
#endif
#ifdef BSD_UTMP
    gSendStrN(*ut->ut_user ? ut->ut_user : 0, sizeof(ut->ut_user));
#else
    gSendStrN(ut->ut_type == USER_PROCESS ? ut->ut_user : 0, sizeof(ut->ut_user));
#endif
    gSendStr(0);
    gSendInt(isTTY);
}
