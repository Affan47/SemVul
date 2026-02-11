modToChars()
{
    OutBuffer buf;
    buf.reserve(16);
    modToBuffer(&buf);
    buf.writebyte(0);
    return buf.extractData();
}
