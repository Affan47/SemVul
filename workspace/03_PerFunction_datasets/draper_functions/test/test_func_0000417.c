parse_config(config_opts &opts)
{
    FILE *cfg = fopen(opts.config_file, "r");
    if(cfg == NULL)
    {
        Log::error("Couldn't open config file \"%s\"!", opts.config_file);
        usage();
        return;
    }
    char buf[PATH_MAX + 64];
    char *bp;
    int lineno = 0;
    while(fgets(buf, sizeof(buf), cfg))
    {
        ++lineno;
        bp = buf;
        while(isspace(*bp)) ++bp;
        if ((*bp == '\0') || (*bp == '#') || (*bp == '!')) continue;
        if (bp[strlen(bp) - 1] != '\n')
        {
            Log::error("config file %s line %d is too long, and is "
                       "being ignored!", opts.config_file, lineno);
            --lineno;
            continue;
        }
        bp[strlen(bp) - 1] = '\0';


        char *vp = strchr(bp, '=');
        if(vp == NULL)
        {
            Log::error("config file %s line %d seems dain bramaged (no \"=\"), "
                       "and is being ignored.", opts.config_file, lineno);
            continue;
        }
        *vp++ = '\0';
        while (isspace(*vp)) ++vp;
        char *end = bp + strlen(bp) - 1;
        while (isspace(*end) && (end >= bp)) *end-- = '\0';
        end = vp + strlen(vp) - 1;
        while (isspace(*end) && (end >= vp)) *end-- = '\0';

        Log::debug("read %s line %d: \"%s\" = \"%s\"",
                   opts.config_file, lineno, bp, vp);
        parse_config_line(opts, lineno, bp, vp);
    }
    fclose(cfg);
}
