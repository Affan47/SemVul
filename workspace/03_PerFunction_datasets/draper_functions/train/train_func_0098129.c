format_double(double v, char *buf, int n, int dp)
{
    char fmt[15];
    char temp[100];
    int i, ncommas;

    sprintf(fmt, "%%%d.%df", n, dp);
    sprintf(temp, fmt, v);
    strcpy(buf, temp);
    G_insert_commas(temp);
    ncommas = strlen(temp) - strlen(buf);
    for (i = 0; i < ncommas && temp[i] == ' '; i++) {
    }
    strcpy(buf, temp + i);

    return 0;
}
