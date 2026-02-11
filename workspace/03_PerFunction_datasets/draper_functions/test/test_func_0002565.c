clip_own_selection(cbd)
    VimClipboard	*cbd;
{


#ifdef FEAT_X11


    if (cbd->available)
    {
	int was_owned = cbd->owned;

	cbd->owned = (clip_gen_own_selection(cbd) == OK);
	if (!was_owned && cbd == &clip_star)
	{


	    if (cbd->owned
		    && (get_real_state() == VISUAL
					    || get_real_state() == SELECTMODE)
		    && clip_isautosel()
		    && hl_attr(HLF_V) != hl_attr(HLF_VNC))
		redraw_curbuf_later(INVERTED_ALL);
	}
    }
#else

    if (!cbd->owned && cbd->available)
	cbd->owned = (clip_gen_own_selection(cbd) == OK);
#endif
}
