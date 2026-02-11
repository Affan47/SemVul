storeSelf( char* buf)
{
    if (!OptCnt)
        return buf;
    buf = writeUint16(buf, OptType);
    buf = writeUint16(buf, getSize()-4);
    int i=0;
    while(i<OptCnt)
    {
        buf = writeUint16(buf, Options[i]);
        i++;
    }
    return buf;
}
