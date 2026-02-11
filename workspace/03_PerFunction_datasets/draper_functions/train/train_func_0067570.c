D_InitIntroSequence(void)
{
    if(showintro)
    {


        I_SetWindowTitle(gamedescription);
        I_SetGrabMouseCallback(D_StartupGrabCallback);
        I_InitGraphics();
        V_RestoreBuffer();


        rawgfx_startup0   = W_CacheLumpName("STARTUP0", PU_STATIC);
        rawgfx_startp[0]  = W_CacheLumpName("STRTPA1",  PU_STATIC);
        rawgfx_startp[1]  = W_CacheLumpName("STRTPB1",  PU_STATIC);
        rawgfx_startp[2]  = W_CacheLumpName("STRTPC1",  PU_STATIC);
        rawgfx_startp[3]  = W_CacheLumpName("STRTPD1",  PU_STATIC);
        rawgfx_startlz[0] = W_CacheLumpName("STRTLZ1",  PU_STATIC);
        rawgfx_startlz[1] = W_CacheLumpName("STRTLZ2",  PU_STATIC);
        rawgfx_startbot   = W_CacheLumpName("STRTBOT",  PU_STATIC);


        D_IntroBackground();
    }


}
