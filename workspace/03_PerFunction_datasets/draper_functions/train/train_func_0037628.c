hsc_status_misc(HSCPRC * hp, STRPTR s)
{
    if (hp->CB_status_misc)
        (*hp->CB_status_misc) (hp, s);
}
