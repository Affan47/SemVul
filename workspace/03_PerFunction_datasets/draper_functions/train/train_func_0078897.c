draw_block (GnucashGrid *grid,
            SheetBlock *block,
            VirtualLocation virt_loc,
            GdkDrawable *drawable,
            int x, int y, int width, int height)
{
    CellDimensions *cd;
    gint x_paint;
    gint y_paint;
    gint w, h;

    for ( virt_loc.phys_row_offset = 0;
            virt_loc.phys_row_offset < block->style->nrows ;
            virt_loc.phys_row_offset++ )
    {
        for ( virt_loc.phys_col_offset = 0;
                virt_loc.phys_col_offset < block->style->ncols ;
                virt_loc.phys_col_offset++ )
        {
            cd = gnucash_style_get_cell_dimensions
                 (block->style,
                  virt_loc.phys_row_offset,
                  virt_loc.phys_col_offset);

            x_paint = block->origin_x + cd->origin_x;
            if (x_paint > x + width)
                break;

            y_paint = block->origin_y + cd->origin_y;
            if (y_paint > y + height)
                return;

            h = cd->pixel_height;
            w = cd->pixel_width;

            if (w == 0)
                continue;

            if (x_paint + w < x)
                continue;

            if (y_paint + h < y)
                continue;

            draw_cell (grid, block, virt_loc, drawable,
                       x_paint - x, y_paint - y, w, h);
        }
    }
}
