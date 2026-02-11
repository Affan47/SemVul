k5_asn1_encode_int(asn1buf *buf, asn1_intmax val, size_t *len_out)
{
    asn1_error_code ret;
    size_t len = 0;
    long valcopy;
    int digit;

    valcopy = val;
    do {
        digit = valcopy & 0xFF;
        ret = asn1buf_insert_octet(buf, digit);
        if (ret)
            return ret;
        len++;
        valcopy = valcopy >> 8;
    } while (valcopy != 0 && valcopy != ~0);

    if (val > 0 && (digit & 0x80) == 0x80) {
        ret = asn1buf_insert_octet(buf, 0);
        if (ret)
            return ret;
        len++;
    } else if (val < 0 && (digit & 0x80) != 0x80) {
        ret = asn1buf_insert_octet(buf, 0xFF);
        if (ret)
            return ret;
        len++;
    }


    *len_out = len;
    return 0;
}
