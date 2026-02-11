reedit_ifile(save_ifile)
	IFILE save_ifile;
{
	IFILE next;
	IFILE prev;


	unsave_ifile(save_ifile);
	next = next_ifile(save_ifile);
	prev = prev_ifile(save_ifile);
	if (edit_ifile(save_ifile) == 0)
		return;


	if (next != NULL_IFILE && edit_inext(next, 0) == 0)
		return;


	if (prev != NULL_IFILE && edit_iprev(prev, 0) == 0)
		return;


	quit(QUIT_ERROR);
}
