append_long_to_string(long val, int base, string &str_val)
{


    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    ldiv_t r;

    if (base > 36 || base < 2) {

        std::invalid_argument ex("The parameter base has an invalid value.");
        throw ex;
    }
    if (val < 0)
        str_val += '-';
    r = ldiv(labs(val), base);


    if (r.quot > 0)
        append_long_to_string(r.quot, base, str_val);


    str_val += digits[(int)r.rem];
}
