bdf_free_glyph_grid(bdf_glyph_grid_t *grid)
#else
bdf_free_glyph_grid(grid)
bdf_glyph_grid_t *grid;
#endif
{
    if (grid == 0)
      return;

    if (grid->name != 0)
      free(grid->name);
    if (grid->bytes > 0)
      free((char *) grid->bitmap);
    if (grid->sel.bytes > 0)
      free((char *) grid->sel.bitmap);
    free((char *) grid);
}
