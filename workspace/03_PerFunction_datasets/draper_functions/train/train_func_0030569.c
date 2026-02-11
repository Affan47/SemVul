SpriteLumpNeeded(lumpinfo_t *lump)
{
    sprite_frame_t *sprite;
    int angle_num;
    int i;

    if (!ValidSpriteLumpName(lump->name))
    {
        return true;
    }


    sprite = FindSpriteFrame(lump->name, lump->name[4]);
    angle_num = lump->name[5] - '0';

    if (angle_num == 0)
    {


        for (i=0; i<8; ++i)
        {
            if (sprite->angle_lumps[i] == lump)
                return true;
        }
    }
    else
    {


        if (sprite->angle_lumps[angle_num - 1] == lump)
            return true;
    }


    if (lump->name[6] == '\0')
        return false;

    sprite = FindSpriteFrame(lump->name, lump->name[6]);
    angle_num = lump->name[7] - '0';

    if (angle_num == 0)
    {


        for (i=0; i<8; ++i)
        {
            if (sprite->angle_lumps[i] == lump)
                return true;
        }
    }
    else
    {


        if (sprite->angle_lumps[angle_num - 1] == lump)
            return true;
    }

    return false;
}
