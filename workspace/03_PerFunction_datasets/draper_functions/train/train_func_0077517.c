tryauth(client *cl, const char *user)
{
    extern bool requestmasterf(const char *fmt, ...);
    if(!nextauthreq) nextauthreq = 1;
    cl->authreq = nextauthreq++;
    filtertext(cl->authname, user, false, 100);
    if(!requestmasterf("reqauth %u %s\n", cl->authreq, cl->authname))
    {
        cl->authreq = 0;
        sendf(cl->clientnum, 1, "ris", SV_SERVMSG, "not connected to authentication server");
    }
}
