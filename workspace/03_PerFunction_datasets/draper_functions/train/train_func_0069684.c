I_GraphicsCheckCommandLine(void)
{
    int i;


    noblit = M_CheckParm ("-noblit");


    if (M_CheckParm("-grabmouse"))
    {
        grabmouse = true;
    }


    if (M_CheckParm("-nograbmouse"))
    {
        grabmouse = false;
    }


    if (M_CheckParm("-window") || M_CheckParm("-nofullscreen"))
    {
        fullscreen = false;
    }


    if (M_CheckParm("-fullscreen"))
    {
        fullscreen = true;
    }


    nomouse = M_CheckParm("-nomouse") > 0;


    i = M_CheckParmWithArgs("-width", 1);

    if (i > 0)
    {
        screen_width = atoi(myargv[i + 1]);
    }


    i = M_CheckParmWithArgs("-height", 1);

    if (i > 0)
    {
        screen_height = atoi(myargv[i + 1]);
    }


    i = M_CheckParmWithArgs("-bpp", 1);

    if (i > 0)
    {
        screen_bpp = atoi(myargv[i + 1]);
    }


    if (M_CheckParm("-8in32"))
    {
        screen_bpp = 32;
    }


    i = M_CheckParmWithArgs("-geometry", 1);

    if (i > 0)
    {
        int w, h;

        if (sscanf(myargv[i + 1], "%ix%i", &w, &h) == 2)
        {
            screen_width = w;
            screen_height = h;
        }
    }


    if (M_CheckParm("-1"))
    {
        SetScaleFactor(1);
    }


    if (M_CheckParm("-2"))
    {
        SetScaleFactor(2);
    }


    if (M_CheckParm("-3"))
    {
        SetScaleFactor(3);
    }


    if (M_CheckParm("-novert"))
    {
        novert = true;
    }


    if (M_CheckParm("-nonovert"))
    {
        novert = false;
    }
}
