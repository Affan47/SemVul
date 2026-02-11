gtoken(char *s)
{
    size_t      len;
    int         token;

    const char *err1 = "Illegal argument: %s.\n";


    if (s[0] == '-') {
        token = ERR;
        len = HDstrlen(&s[1]);
        switch (s[1]) {
        case 'o':
            if (!HDstrncmp("outfile", &s[1], len))
                token = OPT_o;
            break;

        case 'c':
            if (!HDstrncmp("config", &s[1], len))
                token = OPT_c;
            break;

        case 'h':
            if (!HDstrncmp("help", &s[1], len))
                token = OPT_h;
            break;

        case 'd':
            if (!HDstrncmp("dims", &s[1], len))
                token = OPT_d;
            break;

        case 'p':
            if (!HDstrncmp("path", &s[1], len))
                token = OPT_p;
            break;

        case 't':
            if (!HDstrncmp("type", &s[1], len))
                token = OPT_t;
            break;

        case 's':
            if (!HDstrncmp("size", &s[1], len))
                token = OPT_s;
            break;
        }

        if (token == ERR)
            (void) HDfprintf(stderr, err1, s);
    }
    else {
        token = FILNAME;
    }
    return (token);
}
