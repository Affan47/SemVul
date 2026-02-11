goo_canvas_update_grid_line_visibility (GooCanvasTableData *table_data)
{
  GooCanvasTableLayoutData *layout_data;
  GooCanvasTableChild *table_child;
  guint32 grid_line_size;
  gint d, d2, child_num, i, j;

  layout_data = table_data->layout_data;
  for (d = 0; d < 2; d++)
    {

      d2 = 1 - d;


      grid_line_size = ((table_data->dimensions[d2].size + 31) / 32);


      for (i = 0; i + 1 < table_data->dimensions[d].size; i++)
	{
	  layout_data->dldata[d][i].grid_line_visibility
	    = g_realloc (layout_data->dldata[d][i].grid_line_visibility,
			 grid_line_size * sizeof (guint32));
	  memset (layout_data->dldata[d][i].grid_line_visibility, 0xff,
		  grid_line_size * sizeof (guint32));
	}


      for (child_num = 0; child_num < table_data->children->len; child_num++)
        {
          table_child = &g_array_index (table_data->children,
					GooCanvasTableChild, child_num);


          for (i = table_child->start[d];
	       i < table_child->start[d] + table_child->size[d] - 1;
	       i++)
            {

              for (j = table_child->start[d2];
		   j < table_child->start[d2] + table_child->size[d2];
		   j++)
                {
                  GOO_CANVAS_TABLE_UNSET_GRID_LINE_VISIBILITY (layout_data->dldata[d], i, j);
                }
            }
        }
    }
}
