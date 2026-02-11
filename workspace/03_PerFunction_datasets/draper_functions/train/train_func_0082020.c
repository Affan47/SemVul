backward_search_finished (GtkSourceSearchContext *search_context,
			  GAsyncResult           *result,
			  TestSearch             *search)
{
	GtkTextIter match_start;
	GtkTextIter match_end;

	if (gtk_source_search_context_backward_finish (search_context,
						       result,
						       &match_start,
						       &match_end,
						       NULL))
	{
		select_search_occurrence (search, &match_start, &match_end);
	}
}
