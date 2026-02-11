gnm_search_replace_query_fail (GnmSearchReplace *sr,
			       const GnmSearchReplaceCellResult *res)
{
	if (!sr->query_func)
		return;

	sr->query_func (GNM_SRQ_FAIL, sr,
			res->cell, res->old_text, res->new_text);
}
