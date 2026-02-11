gnm_named_expr_collection_unlink (GnmNamedExprCollection *names)
{
	if (!names)
		return;

	g_hash_table_foreach (names->names,
			      cb_unlink_all_names,
			      NULL);
}
