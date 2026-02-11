ho_layout_get_line_line_mask (const ho_layout * l_page, int block_index,
  int line_index)
{
  ho_bitmap *m_line_mask = NULL;
  ho_bitmap *m_temp = NULL;
  ho_objmap *o_map_lines = NULL;
  int x, y, height, width;
  double vertical_leeway = 0.8;


  o_map_lines =
    ho_objmap_new_from_bitmap (l_page->m_blocks_lines_mask[block_index]);


  ho_objmap_sort_by_reading_index (o_map_lines, 1, l_page->dir);

  x = ho_objmap_get_object (o_map_lines, line_index).x;
  y = ho_objmap_get_object (o_map_lines, line_index).y;
  width = ho_objmap_get_object (o_map_lines, line_index).width;
  height = ho_objmap_get_object (o_map_lines, line_index).height;


  x -= l_page->m_blocks_text[block_index]->font_width;
  y -= (int)(vertical_leeway * (double)height);
  width += 2 * l_page->m_blocks_text[block_index]->font_width;
  height += 2 * (int)(vertical_leeway * (double)height);


  if (x < 0)
    x = 0;
  if (y < 0)
    y = 0;
  if (x + width > l_page->m_blocks_text[block_index]->width)
    width = l_page->m_blocks_text[block_index]->width - x;
  if (y + height > l_page->m_blocks_text[block_index]->height)
    height = l_page->m_blocks_text[block_index]->height - y;

  m_temp = ho_objmap_to_bitmap_by_index (o_map_lines, line_index);

  ho_objmap_free (o_map_lines);

  m_line_mask = ho_bitmap_clone_window (m_temp, x, y, width, height);
  ho_bitmap_free (m_temp);

  return m_line_mask;
}
