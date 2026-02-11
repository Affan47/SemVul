netbeans_close(void)
{
    if (NETBEANS_OPEN)
    {
	netbeans_send_disconnect();
	nb_close_socket();
    }

#ifdef FEAT_BEVAL
    bevalServers &= ~BEVAL_NETBEANS;
#endif

    needupdate = 0;
    inAtomic = 0;
    nb_free();


    coloncmd(":sign unplace *");
    changed_window_setting();
    update_screen(CLEAR);
    setcursor();
    cursor_on();
    out_flush();
#ifdef FEAT_GUI
    if (gui.in_use)
    {
	gui_update_cursor(TRUE, FALSE);
	gui_mch_flush();
    }
#endif
}
