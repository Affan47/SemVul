octstr_base64_to_binary(Octstr *ostr)
{
    long triplet;
    long pos, len;
    long to;
    int quadpos = 0;
    int warned = 0;
    unsigned char *data;

    seems_valid(ostr);
    gw_assert(!ostr->immutable);

    len = ostr->len;
    data = ostr->data;

    if (len == 0)
        return;

    to = 0;
    triplet = 0;
    quadpos = 0;
    for (pos = 0; pos < len; pos++) {
        int c = data[pos];
        int sixbits;

        if (c >= 'A' && c <= 'Z') {
            sixbits = c - 'A';
        } else if (c >= 'a' && c <= 'z') {
            sixbits = 26 + c - 'a';
        } else if (c >= '0' && c <= '9') {
            sixbits = 52 + c - '0';
        } else if (c == '+') {
            sixbits = 62;
        } else if (c == '/') {
            sixbits = 63;
        } else if (c == '=') {


            break;
        } else if (isspace(c)) {

            continue;
        } else {
            if (!warned) {
                warning(0, "Unusual characters in base64 "
                        "encoded text.");
                warned = 1;
            }
            continue;
        }

        triplet = (triplet << 6) | sixbits;
        quadpos++;

        if (quadpos == 4) {
            data[to++] = (triplet >> 16) & 0xff;
            data[to++] = (triplet >> 8) & 0xff;
            data[to++] = triplet & 0xff;
            quadpos = 0;
        }
    }


    switch (quadpos) {
    case 0:
        break;
    case 3:
        data[to++] = (triplet >> 10) & 0xff;
        data[to++] = (triplet >> 2) & 0xff;
        break;
    case 2:
        data[to++] = (triplet >> 4) & 0xff;
        break;
    case 1:
        warning(0, "Bad padding in base64 encoded text.");
        break;
    }

    ostr->len = to;
    data[to] = '\0';

    seems_valid(ostr);
}
