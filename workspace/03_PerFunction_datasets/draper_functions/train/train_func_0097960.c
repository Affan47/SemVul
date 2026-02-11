cff_put_real(cff_writer_t *pcw, floatp f)
{
    if (f == (int)f)
        cff_put_int(pcw, (int)f);
    else {

        char str[50];
        byte b = 0xff;
        const char *p;

        gs_sprintf(str, "%g", f);
        sputc(pcw->strm, CD_REAL);
        for (p = str; ; ++p) {
            int digit;

            switch (*p) {
            case 0:
                goto done;
            case '.':
                digit = 0xa; break;
            case '+':
                continue;
            case '-':
                digit = 0xe; break;
            case 'e': case 'E':
                if (p[1] == '-')
                    digit = 0xc, ++p;
                else
                    digit = 0xb;
                break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                digit = *p - '0';
                break;
            default:
                digit = 0xd;
                break;
            }
            if (b == 0xff)
                b = (digit << 4) + 0xf;
            else {
                sputc(pcw->strm, (byte)((b & 0xf0) + digit));
                b = 0xff;
            }
        }
    done:
        sputc(pcw->strm, b);
    }
}
