readString(Source & source)
{
    unsigned int len = readInt(source);
    unsigned char * buf = new unsigned char[len];
    AutoDeleteArray<unsigned char> d(buf);
    source(buf, len);
    readPadding(len, source);
    return string((char *) buf, len);
}
