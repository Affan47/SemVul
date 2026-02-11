pole_is_covered   (sat_t *sat)
{
    int ret1,ret2;
    gdouble qrb1, qrb2, az1, az2;

    ret1 = qrb (sat->ssplon, sat->ssplat, 0.0, 90.0, &qrb1, &az1);
    ret2 = qrb (sat->ssplon, sat->ssplat, 0.0, -90.0, &qrb2, &az2);

    if ((qrb1 <= 0.5*sat->footprint) || (qrb2 <= 0.5*sat->footprint))
        return TRUE;

    return FALSE;
}
