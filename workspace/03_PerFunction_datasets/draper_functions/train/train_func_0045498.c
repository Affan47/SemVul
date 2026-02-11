cputc(int c, MMIOT *f)
{
    switch (c) {
    case '&':   Qstring("&amp;", f); break;
    case '>':   Qstring("&gt;", f); break;
    case '<':   Qstring("&lt;", f); break;
    default :   Qchar(c, f); break;
    }
}
