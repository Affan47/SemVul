readentry(FILE *rfile, struct toptenentry *tt)
{
#ifdef NO_SCAN_BRACK
    static const char fmt[] = "%d %d %d %ld %d %d %d %d %d %d %ld %ld %d%*c";
    static const char fmt32[] = "%c%c %s %s%*c";
    static const char fmt33[] = "%s %s %s %s %s %s%*c";
#else
    static const char fmt[] = "%d.%d.%d %ld %d %d %d %d %d %d %ld %ld %d ";
    static const char fmt32[] = "%c%c %[^,],%[^\n]%*c";
    static const char fmt33[] = "%s %s %s %s %[^,],%[^\n]%*c";
#endif

#ifdef UPDATE_RECORD_IN_PLACE

    final_fpos = tt->fpos = ftell(rfile);
#endif
#define TTFIELDS 13
    if(fscanf(rfile, fmt,
              &tt->ver_major, &tt->ver_minor, &tt->patchlevel,
              &tt->points, &tt->deathdnum, &tt->deathlev,
              &tt->maxlvl, &tt->hp, &tt->maxhp, &tt->deaths,
              &tt->deathdate, &tt->birthdate,
              &tt->uid) != TTFIELDS)
#undef TTFIELDS
            tt->points = 0;
    else
    {

        if (tt->ver_major < 3 ||
            (tt->ver_major == 3 && tt->ver_minor < 3))
        {
            int i;

            if (fscanf(rfile, fmt32,
                       tt->plrole, tt->plgend,
                       tt->name, tt->death) != 4)
                    tt->points = 0;
            tt->plrole[1] = '\0';
            if ((i = str2role(tt->plrole)) >= 0)
                    strcpy(tt->plrole, roles[i].filecode);
            strcpy(tt->plrace, "?");
            strcpy(tt->plgend, (tt->plgend[0] == 'M') ? "Mal" : "Fem");
            strcpy(tt->plalign, "?");
        }
        else if (fscanf(rfile, fmt33,
                        tt->plrole, tt->plrace, tt->plgend,
                        tt->plalign, tt->name, tt->death) != 6)
                tt->points = 0;
#ifdef NO_SCAN_BRACK
        if(tt->points > 0)
        {
            nsb_unmung_line(tt->name);
            nsb_unmung_line(tt->death);
        }
#endif
    }


    if (tt->points > 0)
    {
        if (tt->birthdate < 19000000L) tt->birthdate += 19000000L;
        if (tt->deathdate < 19000000L) tt->deathdate += 19000000L;
    }
}
