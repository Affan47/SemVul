WriteProperty(FILE * pf, const char *szName, char *szValue)
{

    if (!szValue || !*szValue)
        return;

    fputs(szName, pf);
    putc('[', pf);
    WriteEscapedString(pf, szValue, FALSE);
    putc(']', pf);
}
