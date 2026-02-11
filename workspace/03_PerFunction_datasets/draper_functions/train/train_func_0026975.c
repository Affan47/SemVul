toCBuffer(OutBuffer *buf, HdrGenState *hgs)
{
    buf->writestring(sd->toChars());
    buf->writeByte('(');


    if (stageflags & stageToCBuffer)
        buf->writestring("<recursion>");
    else
    {
        int old = stageflags;
        stageflags |= stageToCBuffer;
        argsToCBuffer(buf, elements, hgs);
        stageflags = old;
    }

    buf->writeByte(')');
}
