gda_set_source_get_type (void)
{
	static GType type = 0;

	if (G_UNLIKELY (type == 0)) {
        if (type == 0)
			type = g_boxed_type_register_static ("GdaSetSource",
							     (GBoxedCopyFunc) gda_set_source_copy,
							     (GBoxedFreeFunc) gda_set_source_free);
	}

	return type;
}
