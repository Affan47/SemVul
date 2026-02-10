gck_builder_add_exceptv (GckBuilder *builder,
                         GckAttributes *attrs,
                         const gulong *except_types,
                         guint n_except_types)
{
	gulong i;
	guint j;

	g_return_if_fail (builder != NULL);
	g_return_if_fail (attrs != NULL);

	for (i = 0; i < attrs->count; i++) {
		for (j = 0; j < n_except_types; j++) {
			if (attrs->data[i].type == except_types[j])
				break;
		}
		if (j == n_except_types)
			builder_copy (builder, &attrs->data[i], FALSE);
	}
}
