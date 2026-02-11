OutPrompt(s)

char *s;
{
    char c;

    if (logfp) (void)fprintf(logfp,"%s\n",s);
    if (strlen(s) > FB.fNumColumns - 8) {

        c = s[FB.fNumColumns - 8];
        s[FB.fNumColumns - 8] = '\0';
        ShowPrompt(s);
        s[FB.fNumColumns - 8] = c;
    }
    else
        ShowPrompt(s);

}
