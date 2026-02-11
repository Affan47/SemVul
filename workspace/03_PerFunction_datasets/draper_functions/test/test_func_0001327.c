gl_merge_text_get_key_list (const glMerge *merge)
{
	glMergeText   *merge_text;
	gint           i_field, n_fields;
	GList         *key_list;

	gl_debug (DEBUG_MERGE, "BEGIN");

	merge_text = GL_MERGE_TEXT (merge);

        if ( merge_text->priv->line1_has_keys )
        {
                n_fields = merge_text->priv->keys->len;
        }
        else
        {
                n_fields = merge_text->priv->n_fields_max;
        }

        key_list = NULL;
        for ( i_field=0; i_field < n_fields; i_field++ )
        {
                key_list = g_list_append (key_list, key_from_index(merge_text, i_field));
        }

	gl_debug (DEBUG_MERGE, "END");

	return key_list;
}
