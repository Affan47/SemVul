gnucash_sheet_finalize (GObject *object)
{
    GnucashSheet *sheet;

    sheet = GNUCASH_SHEET (object);

    g_table_destroy (sheet->blocks);
    sheet->blocks = NULL;

    gnucash_sheet_clear_styles (sheet);

    g_hash_table_destroy (sheet->cursor_styles);
    g_hash_table_destroy (sheet->dimensions_hash_table);

    if (G_OBJECT_CLASS (sheet_parent_class)->finalize)
        (*G_OBJECT_CLASS (sheet_parent_class)->finalize)(object);


    gnucash_sheet_im_context_reset(sheet);
    g_object_unref (sheet->im_context);


    g_object_unref (sheet->entry);
}
