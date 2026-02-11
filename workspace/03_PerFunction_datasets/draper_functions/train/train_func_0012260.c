reorder_important_classes (void)
{
  int i;

  for (i = 0; i < N_REG_CLASSES; i++)
    cover_class_order[i] = -1;
  for (i = 0; i < ira_reg_class_cover_size; i++)
    cover_class_order[ira_reg_class_cover[i]] = i;
  qsort (ira_important_classes, ira_important_classes_num,
	 sizeof (enum reg_class), comp_reg_classes_func);
}
