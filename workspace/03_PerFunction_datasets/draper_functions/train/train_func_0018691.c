make_new_column (CsvImportTrans* info, int col, int dx, gboolean test_only)
{
    PangoLayout *layout;
    PangoFontDescription *font_desc;
    int charindex, width;
    GtkCellRenderer *cell =	gnc_csv_preview_get_cell_renderer(info, col);
    int colstart, colend;
    GError* error = NULL;

    colstart = (col == 0)
               ? 0
               : stf_parse_options_fixed_splitpositions_nth (info->parse_data->options, col - 1);
    colend = stf_parse_options_fixed_splitpositions_nth (info->parse_data->options, col);

    g_object_get (G_OBJECT (cell), "font_desc", &font_desc, NULL);
    layout = gtk_widget_create_pango_layout (GTK_WIDGET (info->treeview), "x");
    pango_layout_set_font_description (layout, font_desc);
    pango_layout_get_pixel_size (layout, &width, NULL);
    if (width < 1) width = 1;
    charindex = colstart + (dx + width / 2) / width;
    g_object_unref (layout);
    pango_font_description_free (font_desc);

    if (charindex <= colstart || (colend != -1 && charindex >= colend))
        return FALSE;

    if (!test_only)
    {
        stf_parse_options_fixed_splitpositions_add (info->parse_data->options, charindex);
        if (gnc_csv_parse(info->parse_data, FALSE, &error))
        {
            gnc_error_dialog(NULL, "%s", error->message);
            return FALSE;
        }
        gnc_csv_preview_update_assist (info);
    }

    return TRUE;
}
