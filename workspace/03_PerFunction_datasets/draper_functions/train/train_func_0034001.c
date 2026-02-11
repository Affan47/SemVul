SetTitle(const char *s)
{
    GETWIN(wid)->SetLabel (sci2wx(s));
}
