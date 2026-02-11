name_matches(char *name, struct dump_args *args)
{
#if HAVE_REGCOMP
    regex_t reg;
    regmatch_t rmatch;
    int st;
    char errmsg[BUFSIZ];
#elif   HAVE_REGEXP_H
    char regexp_buffer[RE_BUF_SIZE];
#elif   HAVE_RE_COMP
    extern char *re_comp();
    char *re_result;
#endif
    int i, match;


    match = args->nnames ? 0 : 1;
    for (i = 0; i < args->nnames && !match; i++) {
#if HAVE_REGCOMP

        st = regcomp(&reg, args->names[i], REG_EXTENDED);
        if (st) {
            regerror(st, &reg, errmsg, sizeof(errmsg));
            fprintf(stderr, _("%s: regular expression error: %s\n"), progname,
                    errmsg);
            break;
        }

        st = regexec(&reg, name, 1, &rmatch, 0);
        if (st == 0) {

            if (rmatch.rm_so == 0 && (size_t)rmatch.rm_eo == strlen(name))
                match = 1;
        } else if (st != REG_NOMATCH) {
            regerror(st, &reg, errmsg, sizeof(errmsg));
            fprintf(stderr, _("%s: regular expression match error: %s\n"),
                    progname, errmsg);
            break;
        }
        regfree(&reg);
#elif HAVE_REGEXP_H

        compile(args->names[i], regexp_buffer, &regexp_buffer[RE_BUF_SIZE],
                '\0');
        if (step(name, regexp_buffer)) {
            if (loc1 == name && loc2 == &name[strlen(name)])
                match = 1;
        }
#elif HAVE_RE_COMP

        re_result = re_comp(args->names[i]);
        if (re_result) {
            fprintf(stderr, _("%s: regular expression error: %s\n"), progname,
                    re_result);
            break;
        }
        if (re_exec(name))
            match = 1;
#else

        if (!strcmp(args->names[i], name))
            match = 1;
#endif
    }
    return match;
}
