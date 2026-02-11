toCBuffer2(OutBuffer *buf, HdrGenState *hgs, int mod)
{
    if (mod != this->mod)
    {   toCBuffer3(buf, hgs, mod);
        return;
    }
    buf->writestring(toChars());
}
