odf_fix_expr_names_t_new (OOParseState *state)
{
	odf_fix_expr_names_t *fen = g_new (odf_fix_expr_names_t, 1);

	fen->fixed2orig = g_hash_table_new (g_str_hash, g_str_equal);
	fen->orig2fixed = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
	fen->state = state;
	fen->nexpr = NULL;
	fen->nexpr_name = NULL;

	return fen;
}
