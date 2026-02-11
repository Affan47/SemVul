EV_LightTurnOn
( line_t*       line,
  int           bright )
{
    int         i;
    int         j;
    sector_t*   sector;
    sector_t*   temp;
    line_t*     templine;

    sector = sectors;

    for (i=0;i<numsectors;i++, sector++)
    {
        if (sector->tag == line->tag)
        {


            if (!bright)
            {
                for (j = 0;j < sector->linecount; j++)
                {
                    templine = sector->lines[j];
                    temp = getNextSector(templine,sector);

                    if (!temp)
                        continue;

                    if (temp->lightlevel > bright)
                        bright = temp->lightlevel;
                }
            }
            sector-> lightlevel = bright;
        }
    }
}
