D_Endoom(void)
{
    byte *endoom;


    if (!show_endoom || !main_loop_started || screensaver_mode || testcontrols)
    {
        return;
    }


    endoom = W_CacheLumpName(DEH_String("ENDSTRF"), PU_STATIC);

    I_Endoom(endoom);
}
