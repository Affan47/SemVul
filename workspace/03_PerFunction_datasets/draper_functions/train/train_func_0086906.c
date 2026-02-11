cr_style_get_prop_id (const guchar * a_prop)
{
        gpointer *raw_id = NULL;

        if (!gv_prop_hash) {
                cr_style_init_properties ();
        }

        raw_id = g_hash_table_lookup (gv_prop_hash, a_prop);
        if (!raw_id) {
                return PROP_ID_NOT_KNOWN;
        }
        return GPOINTER_TO_INT (raw_id);
}
