toCBuffer2(OutBuffer *buf, HdrGenState *hgs, int mod)
{
    if (mod != this->mod)
    {   toCBuffer3(buf, hgs, mod);
        return;
    }
    buf->writestring("typeof(");
    exp->toCBuffer(buf, hgs);
    buf->writeByte(')');
    toCBuffer2Helper(buf, hgs);
}
