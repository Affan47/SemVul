cb_pane_init_objs (GnmPane *pane)
{
	Sheet *sheet = scg_sheet (pane->simple.scg);
	GSList *ptr, *list;

	if (sheet != NULL) {


		list = g_slist_reverse (g_slist_copy (sheet->sheet_objects));
		for (ptr = list; ptr != NULL ; ptr = ptr->next)
			sheet_object_new_view (ptr->data,
				(SheetObjectViewContainer *)pane);
		g_slist_free (list);
	}
}
