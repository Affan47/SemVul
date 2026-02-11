row_moved(GtkCMCList *clist, gint srcpos, gint destpos, FolderSortDialog *dialog)
{
	if (dialog->selected == -1)
		return;
	else if (srcpos == dialog->selected)
		set_selected(dialog, destpos);
	else if (srcpos < dialog->selected && destpos >= dialog->selected)
		set_selected(dialog, dialog->selected - 1);
	else if (srcpos > dialog->selected && destpos <= dialog->selected)
		set_selected(dialog, dialog->selected + 1);
}
