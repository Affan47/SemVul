cx_hist_prev(void)
{
	if (pn_index >= hs_cnt - 1) {
		win_remark("bottom of the history list");
		return;
	}

	if (++pn_index == 0)
		us_xchg(&save_line,&line_cmd.line);
	edit_putstr(USTR(history[pn_index]->cmd));
	warn_fail(pn_index);
}
