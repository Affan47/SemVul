callsign(char *s, const char *call)
{
    char cp[17];
    if (strlen(call) > 14)
        return false;

    strncpy(cp,call,14);
    strcat(cp,">");
    char *ss = strstr(s,cp);

    if (ss != NULL)
        return true ;
    else
        return false;
}
