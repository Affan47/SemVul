sendTCF(const Class2Params& params, u_int ms)
{
    u_int tcfLen = params.transferSize(ms);
    u_char* tcf = new u_char[tcfLen];
    memset(tcf, 0, tcfLen);
    bool ok = transmitData(curcap->value, tcf, tcfLen, frameRev, true);
    delete tcf;
    return ok;
}
