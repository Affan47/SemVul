_scroll_region(TERM_REC *term, int y1, int y2, int count)
{

        scroll_region_setup(term, y1, y2);

	term->move(term, 0, y1);
	if (count > 0) {
		term->move(term, 0, y2);
		tput(tparm(term->TI_indn, count, count));
	} else if (count < 0) {
		term->move(term, 0, y1);
		tput(tparm(term->TI_rin, -count, -count));
	}


        scroll_region_setup(term, 0, term->height-1);
}
