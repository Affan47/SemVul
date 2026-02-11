plan_0(int t)
{

  if (t < 0)
    return SCHEDULER_ERROR;

  if (t == 0)
    tenm_table_add(plan_0_more_1_new());


  return SCHEDULER_SUCCESS;
}
