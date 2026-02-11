DEH_MapHereticFrameNumber(int frame)
{
    if (deh_hhe_version < deh_hhe_1_2)
    {


        if (frame >= S_PLAY_FDTH19)
        {
            frame = (frame - S_PLAY_FDTH19) + S_BLOODYSKULL1;
        }
    }
    else
    {


        if (frame >= S_PHOENIXFXIX_1)
        {
            frame = (frame - S_PHOENIXFXIX_1) + S_PHOENIXPUFF1;
        }
    }

    return frame;
}
