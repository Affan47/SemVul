prettyPrintDsymbol(OutBuffer *buf, Dsymbol *s, Dsymbol *parent)
{
    if (s->parent && (s->parent == parent))
    {
        buf->writestring(s->toChars());
    }
    else
    if (!inSameModule(s, parent))
    {
        buf->writestring(s->toPrettyChars());
    }
    else
    {

        if (!parent->isModule() && !parent->isPackage())
            buf->writestring(".");

        parentToBuffer(buf, s->parent);
        buf->writestring(s->toChars());
    }
}
