format_template_new (void)
{
	GnmFormatTemplate *ft;

	ft = g_new0 (GnmFormatTemplate, 1);

	ft->filename    = NULL;
	ft->author      = g_strdup (go_get_real_name ());
	ft->name        = g_strdup (N_("Name"));
	ft->description = g_strdup ("");

	ft->category = NULL;

	ft->members = NULL;
	ft->number    = TRUE;
	ft->border    = TRUE;
	ft->font      = TRUE;
	ft->patterns  = TRUE;
	ft->alignment = TRUE;

	ft->edges.left   = TRUE;
	ft->edges.right  = TRUE;
	ft->edges.top    = TRUE;
	ft->edges.bottom = TRUE;

	ft->table = g_hash_table_new_full ((GHashFunc)gnm_cellpos_hash,
					   (GEqualFunc)gnm_cellpos_equal,
					   (GDestroyNotify)g_free,
					   (GDestroyNotify)gnm_style_unref);
	ft->invalidate_hash = TRUE;

	range_init (&ft->dimension, 0,0,0,0);

	return ft;
}
