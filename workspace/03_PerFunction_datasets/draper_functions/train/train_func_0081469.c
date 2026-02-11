cleanup()
{
  uint i;
  DBUG_ENTER("Item_func_case::cleanup");
  Item_func::cleanup();
  for (i= 0; i <= (uint)DECIMAL_RESULT; i++)
  {
    delete cmp_items[i];
    cmp_items[i]= 0;
  }
  DBUG_VOID_RETURN;
}
