findone(int zx,int zy,void *num)
{
    struct trap *ttmp;
    struct monst *mtmp;

    if (levl[zx][zy].typ == SDOOR)
    {
        cvt_sdoor_to_door(&levl[zx][zy]);
        magic_map_background(zx, zy, 0);
        newsym(zx, zy);
        (*(int*)num)++;
    }
    else if (levl[zx][zy].typ == SCORR)
    {
        levl[zx][zy].typ = CORR;
        unblock_point(zx,zy);
        magic_map_background(zx, zy, 0);
        newsym(zx, zy);
        (*(int*)num)++;
    }
    else if ((ttmp = t_at(zx, zy)) != 0)
    {
        if (!ttmp->tseen && ttmp->ttyp != STATUE_TRAP)
        {
            ttmp->tseen = 1;
            newsym(zx,zy);
            (*(int*)num)++;
        }
    }
    else if ((mtmp = m_at(zx, zy)) != 0)
    {
        if (mtmp->m_ap_type)
        {
            seemimic(mtmp);
            (*(int*)num)++;
        }
        if (mtmp->mundetected &&
            (is_hider(mtmp->data) || mtmp->data->mlet == S_EEL))
        {
            mtmp->mundetected = 0;
            newsym(zx, zy);
            (*(int*)num)++;
        }
        if (!canspotmon(mtmp) &&
            !glyph_is_invisible(levl[zx][zy].glyph))
        {
            map_invisible(zx, zy);
        }
    }
    else if (glyph_is_invisible(levl[zx][zy].glyph))
    {
        unmap_object(zx, zy);
        newsym(zx, zy);
        (*(int*)num)++;
    }
}
