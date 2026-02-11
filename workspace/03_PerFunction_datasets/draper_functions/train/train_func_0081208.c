edit_nu_kill(void)
{
	if (textline == &line_cmd)
		hist_reset_index();

	textline->curs = textline->size = textline->offset = 0;


	us_copy(&textline->line,"");
}
