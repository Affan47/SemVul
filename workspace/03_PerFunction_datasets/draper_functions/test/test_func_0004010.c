date_decode(fdate_t date, uint32_t *year, uint8_t *month,
                 uint8_t *day)
{
    fdate_t z, f, a, alpha, b, c, d, e;

    date += 0.5;
    z = floor(date);
    f = date - z;

    if (z < 2299161.0) {
        a = z;
    } else {
        alpha = floor((z - 1867216.25) / 36524.25);
        a = z + 1 + alpha - floor(alpha / 4);
    }

    b = a + 1524;
    c = floor((b - 122.1) / 365.25);
    d = floor(365.25 * c);
    e = floor((b - d) / 30.6001);

    *day = (uint8_t) (b - d - floor(30.6001 * e) + f);
    *month = (uint8_t) ((e < 14) ? (e - 1) : (e - 13));
    *year = (uint32_t) ((*month > 2) ? (c - 4716) : (c - 4715));
}
