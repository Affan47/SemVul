copy_funcs(Item **func_ptr, const THD *thd)
{
  Item *func;
  for (; (func = *func_ptr) ; func_ptr++)
  {
    func->save_in_result_field(1);


    if (thd->is_error())
      return TRUE;
  }
  return FALSE;
}
