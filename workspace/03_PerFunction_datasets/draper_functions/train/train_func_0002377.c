awtc_fgets(char *s, int size, FILE *stream) {

    int i;
    for (i = 0; i<(size-1); ++i) {
        int byte = fgetc(stream);
        if (byte == EOF) {
            if (i == 0) return 0;
            break;
        }

        s[i] = byte;
        if (byte == '\n' || byte == '\r') break;
    }
    s[i] = 0;

    return s;
}
