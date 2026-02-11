cmap_load_internal(char *filename)
{
    osfildef *fp;
    static char sig1[] = CMAP_SIG_S100;
    char buf[256];
    uchar lenbuf[2];
    size_t len;
    int sysblk;


    if (filename == 0)
    {

        cmap_init_default();


        return 0;
    }


    fp = osfoprb(filename, OSFTCMAP);
    if (fp == 0)
        return 1;


    if (osfrb(fp, buf, sizeof(sig1))
        || memcmp(buf, sig1, sizeof(sig1)) != 0)
    {
        osfcls(fp);
        return 2;
    }


    G_cmap_id[4] = '\0';
    if (osfrb(fp, G_cmap_id, 4))
    {
        osfcls(fp);
        return 3;
    }


    if (osfrb(fp, lenbuf, 2)
        || (len = osrp2(lenbuf)) > sizeof(G_cmap_ldesc)
        || osfrb(fp, G_cmap_ldesc, len))
    {
        osfcls(fp);
        return 4;
    }


    if (osfrb(fp, G_cmap_input, sizeof(G_cmap_input))
        || osfrb(fp, G_cmap_output, sizeof(G_cmap_output)))
    {
        osfcls(fp);
        return 5;
    }


    if (osfrb(fp, buf, 4))
    {
        osfcls(fp);
        return 6;
    }


    if (!memcmp(buf, "SYSI", 4))
    {

        if (osfrb(fp, lenbuf, 2)
            || (len = osrp2(lenbuf)) > sizeof(buf)
            || osfrb(fp, buf, len))
        {
            osfcls(fp);
            return 7;
        }


        sysblk = TRUE;
    }
    else
    {

        sysblk = FALSE;
    }


    os_advise_load_charmap(G_cmap_id, G_cmap_ldesc, sysblk ? buf : "");


    if (sysblk && osfrb(fp, buf, 4))
    {
        osfcls(fp);
        return 8;
    }


    if (!memcmp(buf, "ENTY", 4))
    {

        for (;;)
        {
            size_t len;
            unsigned int cval;
            char expansion[CMAP_MAX_ENTITY_EXPANSION];


            if (osfrb(fp, buf, 4))
            {
                osfcls(fp);
                return 9;
            }


            len = osrp2(buf);
            cval = osrp2(buf+2);


            if (len == 0 && cval == 0)
                break;


            if (len > CMAP_MAX_ENTITY_EXPANSION
                || osfrb(fp, expansion, len))
            {
                osfcls(fp);
                return 10;
            }


            tio_set_html_expansion(cval, expansion, len);
        }
    }


    osfcls(fp);
    return 0;
}
