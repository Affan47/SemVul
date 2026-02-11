odf_oo_cell_style_attach_condition (OOCellStyle *oostyle, OOCellStyle *cstyle,
				gchar const *condition, gchar const *base)
{
	g_return_if_fail (oostyle != NULL);
	g_return_if_fail (cstyle != NULL);
	g_return_if_fail (condition != NULL);

	if (base == NULL)
		base = "";

	oostyle->styles = g_slist_append (oostyle->styles, odf_oo_cell_style_ref (cstyle));
	oostyle->conditions = g_slist_append (oostyle->conditions, g_strdup (condition));
	oostyle->bases = g_slist_append (oostyle->bases, g_strdup (base));
}
