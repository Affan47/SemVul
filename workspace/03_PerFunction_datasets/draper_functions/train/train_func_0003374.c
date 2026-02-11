extract_inchi_substring(char ** buf, const char *str, size_t slen)
{
size_t i;
char *p, pp;

    *buf = NULL;
    if (str==NULL)
        return;
    if (strlen(str)<1)
        return;

    p = strstr(str, "InChI=");
    if (NULL==p)
        return;

    for (i=0; i<slen; i++)
    {
        pp = p[i];

        if (pp >= 'A' && pp <='Z')   continue;
        if (pp >= 'a' && pp <='z')   continue;
        if (pp >= '0' && pp <='9')   continue;
        switch ( pp )
        {
            case '(':
            case ')':
            case '*':
            case '+':
            case ',':
            case '-':
            case '.':
            case '/':
            case ';':
            case '=':
            case '?':
            case '@': continue;

            default:            break;
        }
        break;
    }

    *buf = (char*) inchi_calloc(i+1, sizeof(char));
    memcpy(*buf, p, i);
    (*buf)[i] = '\0';

    return;
}
