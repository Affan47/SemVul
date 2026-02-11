deleteSpaces(char **str, int afterCommas)
{
    char *n = (*str);
    char *r = (*str);
    int  c  = 0;


    while (*r != '\0') {
        if (isspace(*r) && c >= afterCommas) {
            r++;
        } else {
            if (*r == ',') {
                c++;
            }
            *n = *r;
            r++;
            n++;
        }
    }
    *n = '\0';


}
