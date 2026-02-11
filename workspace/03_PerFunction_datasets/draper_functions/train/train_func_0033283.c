doi_lookup(u_int8_t doi_id)
{
	struct doi     *doi;

	for (doi = LIST_FIRST(&doi_tab); doi && doi->id != doi_id;
	    doi = LIST_NEXT(doi, link));
	return doi;
}
