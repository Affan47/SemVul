gnucash_grid_find_loc_by_pixel (GnucashGrid *grid, gint x, gint y,
                                VirtualLocation *virt_loc)
{
    SheetBlock *block;

    if (virt_loc == NULL)
        return FALSE;

    block = gnucash_grid_find_block_by_pixel (grid, x, y,
            &virt_loc->vcell_loc);
    if (block == NULL)
        return FALSE;

    return gnucash_grid_find_cell_by_pixel (grid, x, y, virt_loc);
}
