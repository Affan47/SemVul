sv_is_range_selected (SheetView const *sv, GnmRange const *r)
{
	GSList *ptr;
	GnmRange const *sr;

	for (ptr = sv_selection_calc_simplification (sv);
	     ptr != NULL ; ptr = ptr->next){
		sr = ptr->data;
		if (range_overlap (sr, r))
			return TRUE;
	}
	return FALSE;
}
