MakeKey(
        const char *station,
        const char *location,
        const char *channel,
        char *key
        )
{
    char *p = key;
    const char *t;


    t = station;
    while (ALNUM(*t)) { t++; }
    if (*t == 0) {


        t = station;
    } else {

        t++;
    }


    while (ALNUM(*t)) {
        *p = toupper(*t); p++;
        t++;
    }

    *p = '-'; p++;

    t = location;

    while (ALNUM(*t)) {
        *p = toupper(*t); p++;
        t++;
    }

    *p = '-'; p++;

    t = channel;

    while (ALNUM(*t)) {
        *p = toupper(*t); p++;
        t++;
    }

    *p = 0;
}
