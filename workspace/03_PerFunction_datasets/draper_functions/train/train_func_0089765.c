recv_token(s, flags, tok)
    int     s;
    int    *flags;
    gss_buffer_t tok;
{
    int     ret;
    unsigned char char_flags;
    unsigned char lenbuf[4];

    ret = read_all(s, (char *) &char_flags, 1);
    if (ret < 0) {
        perror("reading token flags");
        return -1;
    } else if (!ret) {
        if (display_file)
            fputs("reading token flags: 0 bytes read\n", display_file);
        return -1;
    } else {
        *flags = (int) char_flags;
    }

    if (char_flags == 0) {
        lenbuf[0] = 0;
        ret = read_all(s, &lenbuf[1], 3);
        if (ret < 0) {
            perror("reading token length");
            return -1;
        } else if (ret != 3) {
            if (display_file)
                fprintf(display_file,
                        "reading token length: %d of %d bytes read\n", ret, 3);
            return -1;
        }
    } else {
        ret = read_all(s, lenbuf, 4);
        if (ret < 0) {
            perror("reading token length");
            return -1;
        } else if (ret != 4) {
            if (display_file)
                fprintf(display_file,
                        "reading token length: %d of %d bytes read\n", ret, 4);
            return -1;
        }
    }

    tok->length = ((lenbuf[0] << 24)
                   | (lenbuf[1] << 16)
                   | (lenbuf[2] << 8)
                   | lenbuf[3]);
    tok->value = (char *) malloc(tok->length ? tok->length : 1);
    if (tok->length && tok->value == NULL) {
        if (display_file)
            fprintf(display_file, "Out of memory allocating token data\n");
        return -1;
    }

    ret = read_all(s, (char *) tok->value, tok->length);
    if (ret < 0) {
        perror("reading token data");
        free(tok->value);
        return -1;
    } else if ((size_t)ret != tok->length) {
        fprintf(stderr, "sending token data: %d of %d bytes written\n",
                ret, (int) tok->length);
        free(tok->value);
        return -1;
    }

    return 0;
}
