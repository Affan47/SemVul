cmd_set_text_full_check_texpr (GnmCellIter const *iter, GnmExprTop const  *texpr)
{
	if (iter->cell == NULL ||
	    !gnm_expr_top_equal (iter->cell->base.texpr, texpr))
		return VALUE_TERMINATE;
	return NULL;
}
