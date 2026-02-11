HA_CountColumnsInTemplate(char *HA_template, int *ncol, int *nrepeat)
{
    char *s;
    int col=1;

    *nrepeat = 999;

    s = (char *) HA_template;


    while (isspace(*s)) s++;
    if (*s=='&') {*s=' '; *nrepeat = 1; s++;}

    while ( (s=NextAmpersand(s)) && *s != '\0') {
        s++;
        col++;
        if (*s=='&') {*s=' '; *nrepeat = col; s++;}
    }
    *ncol = col;

    diagnostics(5,"ncolumns = %d, nrepeat = %d", *ncol, *nrepeat);
}
