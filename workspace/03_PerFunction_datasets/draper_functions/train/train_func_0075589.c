V_ScreenShot(char *format)
{
    int i;
    char lbmname[16];


    for (i=0; i<=99; i++)
    {
        sprintf(lbmname, format, i);

        if (!M_FileExists(lbmname))
        {
            break;
        }
    }

    if (i == 100)
    {
        I_Error ("V_ScreenShot: Couldn't create a PCX");
    }


    WritePCXfile(lbmname, I_VideoBuffer,
                 SCREENWIDTH, SCREENHEIGHT,
                 W_CacheLumpName (DEH_String("PLAYPAL"), PU_CACHE));
}
