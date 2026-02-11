set_value(string *val, int sz)
{
    if ((var()->type() == dods_str_c || var()->type() == dods_url_c) && val) {
        d_str.resize(sz);
        _capacity = sz;
        for (register int t = 0; t < sz; t++) {
            d_str[t] = val[t];
        }
        set_length(sz);
        set_read_p(true);
        return true;
    }
    else {
        return false;
    }
}
