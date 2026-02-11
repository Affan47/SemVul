ST_Progress(void)
{

#ifdef __WATCOMC__

    I_StartupReadKeys();
#endif

    if (using_graphical_startup)
    {
        static int notchPosition = 0;

        if (notchPosition < ST_MAX_NOTCHES)
        {
            ST_UpdateNotches(notchPosition);
            S_StartSound(NULL, SFX_STARTUP_TICK);

            notchPosition++;
        }
    }

    printf(".");
}
