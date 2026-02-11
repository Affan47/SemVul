netbeans_close(void)
{
    if (!NETBEANS_OPEN)
	return;

    netbeans_send_disconnect();

#ifdef FEAT_GUI_X11
    if (inputHandler != (XtInputId)NULL)
    {
	XtRemoveInput(inputHandler);
	inputHandler = (XtInputId)NULL;
    }
#else
# ifdef FEAT_GUI_GTK
    if (inputHandler != 0)
    {
	gdk_input_remove(inputHandler);
	inputHandler = 0;
    }
# else
#  ifdef FEAT_GUI_W32
    if (inputHandler == 0)
    {
	WSAAsyncSelect(nbsock, s_hwnd, 0, 0);
	inputHandler = -1;
    }
#  endif
# endif
#endif

#ifdef FEAT_BEVAL
    bevalServers &= ~BEVAL_NETBEANS;
#endif

    sock_close(nbsock);
    nbsock = -1;

    needupdate = 0;
    inAtomic = 0;
    nb_free();


    coloncmd(":sign unplace *");
    changed_window_setting();
    update_screen(CLEAR);
    setcursor();
    out_flush();
#ifdef FEAT_GUI
    if (gui.in_use)
    {
	gui_update_cursor(TRUE, FALSE);
	gui_mch_flush();
    }
#endif
}
