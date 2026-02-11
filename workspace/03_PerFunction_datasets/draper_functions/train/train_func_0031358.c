scg_comment_select (SheetControlGUI *scg, GnmComment *cc, int x, int y)
{
	g_return_if_fail (IS_SHEET_CONTROL_GUI (scg));

	if (scg->comment.selected != NULL)
		scg_comment_unselect (scg, scg->comment.selected);

	g_return_if_fail (scg->comment.timer == 0);

	scg->comment.selected = cc;
	scg->comment.timer = g_timeout_add (1000,
		(GSourceFunc)cb_cell_comment_timer, scg);
	scg->comment.x = x;
	scg->comment.y = y;
}
