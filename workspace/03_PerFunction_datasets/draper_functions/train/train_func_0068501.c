depline_appstr(STRPTR s, ULONG * linelen)
{
#define LEADING_BLANKS "   "
    size_t slen = strlen(s);


    if ((*linelen + slen) >= 75)
    {
        D(fprintf(stderr, DHD "break line after %lu chars to avoid %lu\n",
                  *linelen, *linelen + slen));

        app_estr(lines_depend, " \\\n");
        app_estr(lines_depend, LEADING_BLANKS);
        *linelen = strlen(LEADING_BLANKS);
    }

    app_estrch(lines_depend, ' ');
    app_estr(lines_depend, s);
    *linelen = *linelen + slen + 1;
}
