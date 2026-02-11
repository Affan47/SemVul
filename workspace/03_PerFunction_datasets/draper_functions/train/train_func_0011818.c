DEH_HereticInit(void)
{
    int i;


    i = M_CheckParm("-hhever");

    if (i > 0)
    {
        SetHHEVersionByName(myargv[i + 1]);
    }


    if (deh_hhe_version < deh_hhe_1_2)
    {
        states[S_PLAY_FDTH18].nextstate = S_NULL;
    }
}
