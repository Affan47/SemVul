toCBuffer(OutBuffer *buf, HdrGenState *hgs)
{
    buf->writestring("synchronized");
    if (exp)
    {   buf->writebyte('(');
        exp->toCBuffer(buf, hgs);
        buf->writebyte(')');
    }
    if (body)
    {
        buf->writebyte(' ');
        body->toCBuffer(buf, hgs);
    }
}
