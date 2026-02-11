P_FindNextHighestFloor(sector_t * sec, int currentheight)
{
    int i;
    int h;
    int min;
    line_t *check;
    sector_t *other;
    fixed_t height = currentheight;
    fixed_t heightlist[20];

    heightlist[0] = 0;

    for (i = 0, h = 0; i < sec->linecount; i++)
    {
        check = sec->lines[i];
        other = getNextSector(check, sec);
        if (!other)
            continue;
        if (other->floorheight > height)
            heightlist[h++] = other->floorheight;
    }


    min = heightlist[0];
    for (i = 1; i < h; i++)
        if (heightlist[i] < min)
            min = heightlist[i];

    return min;
}
