im_show_info(void)
{
    int	    old_vgetc_busy;

    old_vgetc_busy = vgetc_busy;
    vgetc_busy = TRUE;
    showmode();
    vgetc_busy = old_vgetc_busy;
    if ((State & NORMAL) || (State & INSERT))
	setcursor();
    out_flush();
}
