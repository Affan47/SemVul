column_def_init (const gchar *name, guint size, column_def_size_t size_type,
                 column_def_align_t align, column_display_rendering_f render)
{
	column_def_t *coldef;

	coldef = g_new0 (column_def_t, 1);
	coldef->name = name;
	coldef->size = size;
	coldef->requested_size = size;
	coldef->size_type = size_type;
	coldef->align = align;
	coldef->render = render;

	return coldef;
}
