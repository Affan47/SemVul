WriteCFGFontNumber(char **cfg_stream)


{
    int n=-1;
    char *font_name, *star;

    *cfg_stream += 1;

    if (**cfg_stream == '*') {
        fprintRTF("*");
        return;
    }

    font_name = strdup(*cfg_stream);
    star = strchr(font_name,'*');

    if (star) {
        *star = '\0';
        n = TexFontNumber(font_name);

        if (n < 0)
            diagnostics(ERROR, "Unknown font <%s>\nFound in cfg line <%s>", font_name, cfg_stream);

        *cfg_stream += strlen(font_name);
        fprintRTF("%d",n);
    }

    free(font_name);
}
