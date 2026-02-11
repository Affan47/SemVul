get_no_void_group(int direction)
{
  int index = current_shapelistgroup_index;

  direction = direction>0 ? 1 : -1;

  index += direction;
  while(0 <= index && index < g_list_length(shape_list_group))
    {
      if(get_element_count_listgroup(index))
	return index;
      index += direction;
    }
  return current_shapelistgroup_index;
}
