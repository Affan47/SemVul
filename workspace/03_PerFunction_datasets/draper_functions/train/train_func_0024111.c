hiddenpwd(const char *pwd, int showchars)
{
    static int sc = 3;
    static string text;
    copystring(text, pwd);
    if(showchars > 0) sc = showchars;
    for(int i = (int)strlen(text) - 1; i >= sc; i--) text[i] = '*';
    return text;
}
