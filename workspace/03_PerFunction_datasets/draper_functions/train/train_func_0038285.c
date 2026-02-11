init_outfile(char const *outPath, int decode)
{
    FILE   *outf;


    if (0 == strcmp(outPath, "-")) {
        outf = stdout;
        lame_set_stream_binary_mode(outf);
    }
    else {
        outf = lame_fopen(outPath, "w+b");
#ifdef __riscos__

        if (outf != NULL) {
            char *p, *out_path = strdup(outPath);
            for (p = out_path; *p; p++) {
                switch (*p) {
                case '.':
                    *p = '/';
                    break;
                case '/':
                    *p = '.';
                    break;
                }
            }
            SetFiletype(out_path, decode ? 0xFB1  : 0x1AD );
            free(out_path);
        }
#else
        (void) decode;
#endif
    }
    return outf;
}
