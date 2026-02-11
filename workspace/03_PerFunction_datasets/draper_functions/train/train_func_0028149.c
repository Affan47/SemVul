mm_login_alt_cue(NETMBX *mb)
{
    if(ps_global->ttyo){
	COLOR_PAIR  *lastc;

	lastc = pico_set_colors(ps_global->VAR_TITLE_FORE_COLOR,
				ps_global->VAR_TITLE_BACK_COLOR,
				PSC_REV | PSC_RET);

	mark_titlebar_dirty();
	PutLine0(0, ps_global->ttyo->screen_cols - 1,
		 (mb->sslflag||mb->tlsflag) ? "+" : " ");

	if(lastc){
	    (void)pico_set_colorp(lastc, PSC_NONE);
	    free_color_pair(&lastc);
	}

	fflush(stdout);
    }
}
