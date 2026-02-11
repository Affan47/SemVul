getsearchreturnopts(char *tag, struct searchargs *searchargs)
{
    int c;
    static struct buf opt;

    c = prot_getc(imapd_in);
    if (c != '(') {
        prot_printf(imapd_out,
                    "%s BAD Missing return options in Search\r\n", tag);
        return EOF;
    }

    do {
        c = getword(imapd_in, &opt);
        if (!opt.s[0]) break;

        lcase(opt.s);
        if (!strcmp(opt.s, "min")) {
            searchargs->returnopts |= SEARCH_RETURN_MIN;
        }
        else if (!strcmp(opt.s, "max")) {
            searchargs->returnopts |= SEARCH_RETURN_MAX;
        }
        else if (!strcmp(opt.s, "all")) {
            searchargs->returnopts |= SEARCH_RETURN_ALL;
        }
        else if (!strcmp(opt.s, "count")) {
            searchargs->returnopts |= SEARCH_RETURN_COUNT;
        }
        else {
            prot_printf(imapd_out,
			"%s BAD Invalid Search return option %s\r\n",
                        tag, opt.s);
            return EOF;
        }

    } while (c == ' ');

    if (c != ')') {
        prot_printf(imapd_out,
                    "%s BAD Missing close parenthesis in Search\r\n", tag);
        return EOF;
    }

    c = prot_getc(imapd_in);

    return c;
}
