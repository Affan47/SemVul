find_long_option(spif_charptr_t opt)
{
    spif_int32_t j;

    D_OPTIONS(("opt == \"%s\"\n", NONULL(opt)));

    for (j = 0; j < SPIFOPT_NUMOPTS_GET(); j++) {
        size_t l;

        l = strlen(SPIF_CHARPTR_C(SPIFOPT_OPT_LONG(j)));

        if (!strncasecmp(SPIF_CHARPTR_C(SPIFOPT_OPT_LONG(j)), SPIF_CHARPTR_C(opt), l)
            && (opt[l] == '=' || !opt[l])) {

            D_OPTIONS(("Match found at %d:  %s == %s\n", j, SPIFOPT_OPT_LONG(j), opt));
            return j;
        }
    }


    libast_print_error("Unrecognized long option --%s\n", opt);
    CHECK_BAD();
    return ((spif_int32_t) -1);
}
