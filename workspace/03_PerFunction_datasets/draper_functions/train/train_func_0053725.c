gnm_style_conditions_delete (GnmStyleConditions *sc, guint pos)
{
	g_return_if_fail (sc != NULL);
	g_return_if_fail (sc->conditions != NULL);
	g_return_if_fail (sc->conditions->len > pos);

	gnm_style_cond_free (g_ptr_array_index (sc->conditions, pos));
	if (sc->conditions->len <= 1) {
		g_ptr_array_free (sc->conditions, TRUE);
		sc->conditions = NULL;
	} else
		g_ptr_array_remove_index (sc->conditions, pos);
}
