gnucash_sheet_recompute_block_offsets (GnucashSheet *sheet)
{
    Table *table;
    SheetBlock *block;
    gint i, j;
    gint height;
    gint width;

    g_return_if_fail (sheet != NULL);
    g_return_if_fail (GNUCASH_IS_SHEET(sheet));
    g_return_if_fail (sheet->table != NULL);

    table = sheet->table;

    height = 0;
    block = NULL;
    for (i = 0; i < table->num_virt_rows; i++)
    {
        width = 0;

        for (j = 0; j < table->num_virt_cols; j++)
        {
            VirtualCellLocation vcell_loc = { i, j };

            block = gnucash_sheet_get_block (sheet, vcell_loc);

            block->origin_x = width;
            block->origin_y = height;

            if (block->visible)
                width += block->style->dimensions->width;
        }

        if (i > 0 && block->visible)
            height += block->style->dimensions->height;
    }

    sheet->height = height;
}
