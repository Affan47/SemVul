gitg_diff_iter_get_index (GitgDiffIter  *iter,
                          gchar        **from,
                          gchar        **to)
{
	Region *region = GITG_DIFF_ITER_GET_REGION (iter);

	while (region && region->type != GITG_DIFF_ITER_TYPE_HEADER)
	{
		region = region->prev;
	}

	if (!region)
	{
		return FALSE;
	}

	Header *header = (Header *)region;
	gboolean ret = TRUE;

	if (!* (header->index_to))
	{
		ret = header_parse_index (GITG_DIFF_ITER_GET_VIEW (iter), header);
	}

	if (!ret)
	{
		return FALSE;
	}

	*from = header->index_from;
	*to = header->index_to;

	return TRUE;
}
