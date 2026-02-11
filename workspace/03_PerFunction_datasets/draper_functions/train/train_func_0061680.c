type_filter(const struct gen_info *gen)
{

	const GFileType	tft = dp_row_get_file_type(dp_get_tree_model(gen->src), gen->s_iter->data, TRUE);
	const GFileType	ft = dp_row_get_file_type(dp_get_tree_model(gen->src), gen->s_iter->data, FALSE);
	if((gen->flags & CGF_NODIRS) && (tft == G_FILE_TYPE_DIRECTORY))
		return FALSE;
	else if((gen->flags & CGF_LINKSONLY) && (ft != G_FILE_TYPE_SYMBOLIC_LINK))
		return FALSE;
	return TRUE;
}
