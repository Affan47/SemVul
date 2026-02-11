parseCRideSettingsConfig(WKO_UCHAR *p)
{
    p = parsePerspective(p);
    p += donumber(p, &ul);


    if (version == 12 || version == 1 || version == 7) p += donumber(p,&ul);
    charts--;
    return p;
}
