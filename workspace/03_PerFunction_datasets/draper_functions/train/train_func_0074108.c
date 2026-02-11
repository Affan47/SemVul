valid_win_handler( Display     * dpy  FL_UNUSED_ARG,
                   XErrorEvent * xev )
{
    if ( xev->error_code == BadWindow || xev->error_code == BadDrawable )
        badwin = 1;

    return 0;
}
