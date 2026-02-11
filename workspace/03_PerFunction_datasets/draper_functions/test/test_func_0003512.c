sub_data_div(Sub_data *s, const Sub_data *s0)
{
    int num;
    int den;

    if (sub_data_is_unknown(s))
        return;

    if (sub_data_is_unknown(s0)) {
        sub_data_unknownize(s);
        return;
    }

    if (!sub_data_is_const(s0) || sub_data_is_zero(s0)) {
        sub_data_unknownize(s);
        return;
    }

    if (!sub_data_is_const(s) && sub_data_b(s) != 0) {
        sub_data_unknownize(s);
        return;
    }

    num = sub_data_b(s0);
    den = sub_data_db(s0);
    sub_data_mul_const_int(s, den);
    sub_data_div_const_int(s, num);
}
