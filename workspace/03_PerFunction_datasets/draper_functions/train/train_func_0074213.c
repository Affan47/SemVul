cleanup()
{
  DBUG_ENTER("subselect_single_select_engine::cleanup");
  prepared= optimized= executed= optimize_error= 0;
  join= 0;
  result->cleanup();
  DBUG_VOID_RETURN;
}
