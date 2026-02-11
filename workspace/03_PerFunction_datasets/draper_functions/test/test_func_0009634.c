json_read_double(InputStream * inp) {
    char buf[256];
    int pos = 0;
    double n = 0;
    char * end = buf;

    for (;;) {
        int ch = peek_stream(inp);
        switch (ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-':
        case '+':
        case 'e':
        case 'E':
        case '.':
            if (pos >= (int)sizeof(buf) - 1) exception(ERR_BUFFER_OVERFLOW);
            buf[pos++] = (char)read_stream(inp);
            continue;
        }
        break;
    }
    if (pos == 0) exception(ERR_JSON_SYNTAX);
    buf[pos++] = 0;
    n = strtod(buf, &end);
    if (*end != 0) exception(ERR_JSON_SYNTAX);
    return n;
}
