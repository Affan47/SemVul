Palette_cell_X(byte index)
{
  if (Config.Palette_vertical)
  {
    return (MENU_WIDTH+1+((index-First_color_in_palette)%Menu_cells_X)*Menu_palette_cell_width)*Menu_factor_X;
  }
  else
  {
    return (MENU_WIDTH+1+((index-First_color_in_palette)/Menu_cells_Y)*Menu_palette_cell_width)*Menu_factor_X;
  }
}
