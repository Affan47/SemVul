msg_use_printf()
{
    return (!msg_check_screen()
#if defined(WIN3264) && !defined(FEAT_GUI_MSWIN)
	    || !termcap_active
#endif
	    || (swapping_screen() && !termcap_active)
	       );
}
