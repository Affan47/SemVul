low_pressure_loop_node_p (ira_loop_tree_node_t node)
{
  int i;
  enum reg_class cover_class;

  if (node->bb != NULL)
    return false;

  for (i = 0; i < ira_reg_class_cover_size; i++)
    {
      cover_class = ira_reg_class_cover[i];
      if (node->reg_pressure[cover_class]
	  > ira_available_class_regs[cover_class])
	return false;
    }
  return true;
}
