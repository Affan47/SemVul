cmd_search_replace_update_after_action (CmdSearchReplace *me,
					WorkbookControl *wbc)
{
	GList *tmp;
	Sheet *last_sheet = NULL;

	for (tmp = me->cells; tmp; tmp = tmp->next) {
		SearchReplaceItem *sri = tmp->data;
		if (sri->pos.sheet != last_sheet) {
			last_sheet = sri->pos.sheet;
			update_after_action (last_sheet, wbc);
		}
	}
}
