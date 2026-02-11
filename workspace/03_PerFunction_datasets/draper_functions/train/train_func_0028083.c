write_type2_float(WRF_output * a_output, double a_float)
{
    char buffer[32];
    const char *p = buffer;
    int high = true;
    char c = 0;

    gs_sprintf(buffer, "%f", a_float);
    WRF_wbyte(a_output, 30);
    for (;;) {
        char n = 0;

        if (*p >= '0' && *p <= '9')
            n = (char)(*p - '0');
        else if (*p == '.')
            n = 0xA;
        else if (*p == 'e' || *p == 'E') {
            if (p[1] == '-') {
                p++;
                n = 0xC;
            } else
                n = 0xB;
        } else if (*p == '-')
            n = 0xE;
        else if (*p == 0)
            n = 0xF;
        if (high) {
            if (*p == 0)
                WRF_wbyte(a_output, 0xFF);
            else
                c = (char)(n << 4);
        } else {
            c |= n;
            WRF_wbyte(a_output, c);
        }

        if (*p == 0)
            break;

        high = !high;
        p++;
    }
}
