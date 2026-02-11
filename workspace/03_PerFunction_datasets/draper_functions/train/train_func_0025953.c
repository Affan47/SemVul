hex_to_binary2(const u_char * input, size_t len, char **output)
{
    u_int           olen = (len / 2) + (len % 2);
    char           *s = calloc(1, olen ? olen : 1), *op = s;
    const u_char   *ip = input;


    *output = NULL;
    if (!s)
        goto hex_to_binary2_quit;

    *op = 0;
    if (len % 2) {
        if (!isxdigit(*ip))
            goto hex_to_binary2_quit;
        *op++ = HEX2VAL(*ip);
        ip++;
    }

    while (ip < input + len) {
        if (!isxdigit(*ip))
            goto hex_to_binary2_quit;
        *op = HEX2VAL(*ip) << 4;
        ip++;

        if (!isxdigit(*ip))
            goto hex_to_binary2_quit;
        *op++ += HEX2VAL(*ip);
        ip++;
    }

    *output = s;
    return olen;

  hex_to_binary2_quit:
    free_zero(s, olen);
    return -1;

}
