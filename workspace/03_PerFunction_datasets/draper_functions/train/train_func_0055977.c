gnm_expr_entry_load_from_dep (GnmExprEntry *gee, GnmDependent const *dep)
{
	g_return_if_fail (IS_GNM_EXPR_ENTRY (gee));
	g_return_if_fail (dep != NULL);

	g_return_if_fail (gee->freeze_count == 0);

	if (dep->texpr != NULL) {
		char *text;
		GnmParsePos pp;

		parse_pos_init_dep (&pp, dep);
		text = gnm_expr_top_as_string (dep->texpr, &pp,
					       gee_convs (gee));

		gee_rangesel_reset (gee);
		gtk_entry_set_text (gee->entry, text);
		gee->rangesel.text_end = strlen (text);

		g_free (text);
		gee_delete_tooltip (gee, TRUE);
	} else
		gnm_expr_entry_load_from_text (gee, "");
}
