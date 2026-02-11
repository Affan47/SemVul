toChars()
{
    OutBuffer buf;
    HdrGenState hgs;
    char *s;

    TemplateInstance::toCBuffer(&buf, &hgs);
    s = buf.toChars();
    buf.data = NULL;
    return s;
}
