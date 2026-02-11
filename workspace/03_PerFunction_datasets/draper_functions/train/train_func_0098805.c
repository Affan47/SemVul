low_pressure_loop_node_p (ira_loop_tree_node_t node)
{
  int i;
  enum reg_class pclass;

  if (node->bb != NULL)
    return false;

  for (i = 0; i < ira_pressure_classes_num; i++)
    {
      pclass = ira_pressure_classes[i];
      if (node->reg_pressure[pclass] > ira_available_class_regs[pclass]
	  && ira_available_class_regs[pclass] > 1)
	return false;
    }
  return true;
}
