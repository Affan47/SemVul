timegmw_noleapsecond(struct vtm *vtm)
{
    VALUE year1900;
    VALUE q400, r400;
    int year_mod400;
    int yday;
    long days_in400;
    VALUE vdays, ret;
    wideval_t wret;

    year1900 = sub(vtm->year, INT2FIX(1900));

    divmodv(year1900, INT2FIX(400), &q400, &r400);
    year_mod400 = NUM2INT(r400);

    yday = calc_tm_yday(year_mod400, vtm->mon-1, vtm->mday);


    ret = LONG2NUM(vtm->sec
                 + vtm->min*60
                 + vtm->hour*3600);
    days_in400 = yday
               - 70*365
               + DIV(year_mod400 - 69, 4)
               - DIV(year_mod400 - 1, 100)
               + (year_mod400 + 299) / 400;
    vdays = LONG2NUM(days_in400);
    vdays = add(vdays, mul(q400, INT2FIX(97)));
    vdays = add(vdays, mul(year1900, INT2FIX(365)));
    wret = wadd(rb_time_magnify(v2w(ret)), wmul(rb_time_magnify(v2w(vdays)), WINT2FIXWV(86400)));
    wret = wadd(wret, v2w(vtm->subsecx));

    return wret;
}
