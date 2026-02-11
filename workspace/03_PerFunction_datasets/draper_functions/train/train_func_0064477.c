pit_arg_date(char **arg, char *required)
{
    char format[32];
    time_t now = time(NULL);
    time_t seconds = (time_t)0;
    struct tm *ptm = localtime(&now);
    struct tm tm = { 0 };

    if (required && (!*arg || pit_arg_is_option(arg))) {
        die("missing %s", required);
    } else if (!strcmp(*arg, "none")) {
        return -1;
    } else {
        bool alpha_date = isalpha(**arg);
        bool slash_date = (strchr(*arg, '/') != NULL);

        if (alpha_date && islower(**arg)) {
            **arg = toupper(**arg);
        }

        if (alpha_date || slash_date) {
            if (strchr(*arg, ':')) {
                if (alpha_date) {
                    strcpy(format, "%b %d, %Y %H:%M");
                } else {
                    strcpy(format, "%m/%d/%Y %H:%M");
                }
            } else {
                if (strlen(*arg) >= 12) {
                    if (alpha_date) {
                        strcpy(format, "%b %d, %Y %H");
                    } else {
                        strcpy(format, "%m/%d/%Y %H");
                    }
                } else {
                    if (alpha_date) {
                        strcpy(format, "%b %d, %Y");
                    } else {
                        strcpy(format, "%m/%d/%Y");
                    }
                }
            }
            if (alpha_date) {
                adjust_alpha_date(arg, format);
            } else {
                adjust_slash_date(arg, format);
            }
        } else {
            if (strchr(*arg, ':')) {
                strcpy(format, "%H:%M");
            } else {
                strcpy(format, "%H");
            }
        }
        adjust_time(arg, format);


        if (strptime(*arg, format, &tm)) {

            if (!tm.tm_mday) tm.tm_mday  = ptm->tm_mday;
            if (!tm.tm_mon)  tm.tm_mon   = ptm->tm_mon;
            if (!tm.tm_year) tm.tm_year  = ptm->tm_year;
            tm.tm_isdst = -1;


            seconds = mktime(&tm);

            if (seconds == (time_t)-1) {
                perish("invalid date");
            }
        } else {
            die("invalid %s: %s", required, *arg);
        }
    }

    return seconds;
}
