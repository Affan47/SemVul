fiowfda(osfildef *fp, vocddef *p, uint cnt)
{
    uchar buf[14];
    uint  i;

    for (i = 0 ; i < cnt ; ++i, ++p)
    {
        if (p->vocdfn == MCMONINV) continue;

        oswp2(buf, i);
        oswp2(buf+2, p->vocdfn);
        buf[4] = p->vocdarg.runstyp;
        switch(buf[4])
        {
        case DAT_NUMBER:
            oswp4(buf+5, p->vocdarg.runsv.runsvnum);
            break;
        case DAT_OBJECT:
        case DAT_FNADDR:
            oswp2(buf+5, p->vocdarg.runsv.runsvobj);
            break;
        case DAT_PROPNUM:
            oswp2(buf+5, p->vocdarg.runsv.runsvprp);
            break;
        }
        oswp2(buf+9, p->vocdprp);
        oswp2(buf+11, p->vocdtim);


        if (osfwb(fp, buf, 13)) return(TRUE);
    }


    oswp2(buf, 0xffff);
    return(osfwb(fp, buf, 13));
}
