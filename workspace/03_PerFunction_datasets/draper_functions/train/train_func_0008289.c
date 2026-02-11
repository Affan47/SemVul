set_value(THD *thd,
                                       sp_rcontext * , Item **it)
{
  Item_func_set_user_var *suv= new Item_func_set_user_var(get_name(), *it, false);


  return (!suv || suv->fix_fields(thd, it) || suv->check(0) || suv->update());
}
