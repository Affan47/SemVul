gl_media_select_set_filter_parameters (glMediaSelect  *this,
                                       const gchar    *page_size_id,
                                       const gchar    *category_id)
{
        gchar *page_size_name;
        gchar *category_name;

        gl_debug (DEBUG_MEDIA_SELECT, "START");

        page_size_name = lgl_db_lookup_paper_name_from_id (page_size_id);
        if (page_size_name == NULL)
        {
                page_size_name = g_strdup (C_("Page size", "Any"));
        }

        gl_combo_util_set_active_text (GTK_COMBO_BOX (this->priv->page_size_combo),
                                       page_size_name);

        category_name = lgl_db_lookup_category_name_from_id (category_id);
        if (category_name == NULL)
        {
                category_name = g_strdup (C_("Category", "Any"));
        }

        gl_combo_util_set_active_text (GTK_COMBO_BOX (this->priv->category_combo),
                                       category_name);
        g_free (page_size_name);
        g_free (category_name);

        gl_debug (DEBUG_MEDIA_SELECT, "END");
}
