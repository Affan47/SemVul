unshowmode(force)
    int	    force;
{


    if (!redrawing() || (!force && char_avail() && !KeyTyped))
	redraw_cmdline = TRUE;
    else
    {
	msg_pos_mode();
	if (Recording)
	    MSG_PUTS_ATTR(_("recording"), hl_attr(HLF_CM));
	msg_clr_eos();
    }
}
