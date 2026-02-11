cleanZarg(char *input)
{
    char *pcbuf;
    int   k = 0;

    pcbuf = strdup(input);
    while ((pcbuf[k] != '\0') && (pcbuf[k] != '\"'))
	k++;
    pcbuf[k] = '\0';

    return pcbuf;
}
