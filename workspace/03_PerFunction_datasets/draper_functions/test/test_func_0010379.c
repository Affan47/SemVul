config_read_config(Config *conf, const char *name)
{
    int c;
    FILE* fin = fopen(name, "r");

    if(fin == NULL) {
        char error[512];
        snprintf(error, 512, "config file not found: %s\n", name);
        logger_log("config", LL_WARNING, error);
        return;
    }

    c = fgetc(fin);
    while(! feof(fin)) {
        char cc = c;

        consume_whitespace(fin);

        if(cc == '#') {
            consume_comment(fin);
        } else {
            ungetc(c, fin);

            consume_whitespace(fin);

            consume_line(conf, fin);

            consume_whitespace(fin);
        }

        consume_whitespace(fin);

        c = fgetc(fin);
    }

    fclose(fin);
}
