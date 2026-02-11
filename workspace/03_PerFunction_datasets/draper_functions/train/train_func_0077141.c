P_UnArchiveWorld(void)
{
    int i, j;
    sector_t *sec;
    line_t *li;
    side_t *si;


    for (i = 0, sec = sectors; i < numsectors; i++, sec++)
    {
        sec->floorheight = SV_ReadWord() << FRACBITS;
        sec->ceilingheight = SV_ReadWord() << FRACBITS;
        sec->floorpic = SV_ReadWord();
        sec->ceilingpic = SV_ReadWord();
        sec->lightlevel = SV_ReadWord();
        sec->special = SV_ReadWord();
        sec->tag = SV_ReadWord();
        sec->specialdata = 0;
        sec->soundtarget = 0;
    }


    for (i = 0, li = lines; i < numlines; i++, li++)
    {
        li->flags = SV_ReadWord();
        li->special = SV_ReadWord();
        li->tag = SV_ReadWord();
        for (j = 0; j < 2; j++)
        {
            if (li->sidenum[j] == -1)
                continue;
            si = &sides[li->sidenum[j]];
            si->textureoffset = SV_ReadWord() << FRACBITS;
            si->rowoffset = SV_ReadWord() << FRACBITS;
            si->toptexture = SV_ReadWord();
            si->bottomtexture = SV_ReadWord();
            si->midtexture = SV_ReadWord();
        }
    }
}
