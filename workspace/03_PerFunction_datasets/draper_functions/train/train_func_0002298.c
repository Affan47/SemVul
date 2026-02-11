streamLengthOfValue(DcmVR& vr)
{
    static char buf[256];
    Uint32 min = vr.getMinValueLength();
    Uint32 max = vr.getMaxValueLength();
    Uint32 undefLen = DCM_UndefinedLength;

    if (min==max) {
        sprintf(buf, "%d bytes fixed length", (int)min);
    } else if (min==0) {
        if (max==undefLen) {
            sprintf(buf, "unrestricted length");
        } else {
            sprintf(buf, "%d bytes maximum", (int)max);
        }
    } else {
        sprintf(buf, "range %d-%d bytes length", (int)min, (int)max);
    }
    return buf;
}
