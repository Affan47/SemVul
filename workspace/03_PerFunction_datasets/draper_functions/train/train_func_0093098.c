charset_latin1_to_gsm(Octstr *ostr)
{
    long pos, len;
    int c, new;
    unsigned char esc = 27;

    len = octstr_len(ostr);
    for (pos = 0; pos < len; pos++) {
    c = octstr_get_char(ostr, pos);
    gw_assert(c >= 0);
    gw_assert(c <= 256);
    new = latin1_to_gsm[c];
    if (new < 0) {

        octstr_insert_data(ostr, pos, (char*) &esc, 1);
        pos++;
        len++;
        new = -new;
    }
    if (new != c)
        octstr_set_char(ostr, pos, new);
    }
}
