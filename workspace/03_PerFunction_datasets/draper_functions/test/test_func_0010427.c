locus_destroy(struct view *view, locus_t locus)
{
	if (locus < view->loci)
		view->locus[locus] = DELETED;
}
