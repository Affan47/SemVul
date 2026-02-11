ira_init_costs (void)
{
  int i;

  free_ira_costs ();
  max_struct_costs_size
    = sizeof (struct costs) + sizeof (int) * (ira_important_classes_num - 1);

  init_cost = (struct costs *) xmalloc (max_struct_costs_size);
  init_cost->mem_cost = 1000000;
  for (i = 0; i < ira_important_classes_num; i++)
    init_cost->cost[i] = 1000000;
  for (i = 0; i < MAX_RECOG_OPERANDS; i++)
    {
      op_costs[i] = (struct costs *) xmalloc (max_struct_costs_size);
      this_op_costs[i] = (struct costs *) xmalloc (max_struct_costs_size);
    }
  temp_costs = (struct costs *) xmalloc (max_struct_costs_size);
  cost_classes = (enum reg_class *) xmalloc (sizeof (enum reg_class)
					     * ira_important_classes_num);
}
