ui_delay(msec, ignoreinput)
    long	msec;
    int		ignoreinput;
{
#ifdef FEAT_GUI
    if (gui.in_use && !ignoreinput)
	gui_wait_for_chars(msec);
    else
#endif
	mch_delay(msec, ignoreinput);
}
