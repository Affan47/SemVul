operator<(const PartialDate& d1, const PartialDate& d2)
{
    return d2.year() > d1.year() ||
           ((d2.year() == d1.year()) &&
            (d2.month() > d1.month() || (d2.month() == d1.month() && d2.day() > d1.day())));
}
