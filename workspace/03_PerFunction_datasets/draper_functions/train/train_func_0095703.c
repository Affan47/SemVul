dial(const char* number, Status& eresult)
{
    dialedNumber = fxStr(number);
    protoTrace("DIAL %s", number);
    fxStr buf = fxStr::format((const char*) conf.dialCmd, number);
    eresult.clear();
    CallStatus cs = (atCmd(buf, AT_NOTHING) ? dialResponse(eresult) : FAILURE);
    if (cs != OK && eresult.value() == 0) {
        eresult = callStatus[cs];
    }
    return (cs);
}
