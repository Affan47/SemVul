compare_const(Item *c)
{
  if (compare_as_dates)
  {
    cmp.set_datetime_cmp_func(this, &c, &const_item);
    cond_false= cmp.compare();
  }
  else
  {
    Item_func_eq *func= new Item_func_eq(c, const_item);
    func->set_cmp_func();
    func->quick_fix_field();
    cond_false= !func->val_int();
  }
  if (cond_false)
    const_item_cache= 1;
}
