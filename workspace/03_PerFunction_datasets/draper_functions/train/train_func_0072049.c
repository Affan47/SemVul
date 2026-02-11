eq(const Item *item, bool binary_cmp) const
{
  Item_date_add_interval *other= (Item_date_add_interval*) item;
  if (!Item_func::eq(item, binary_cmp))
    return 0;
  return ((int_type == other->int_type) &&
          (date_sub_interval == other->date_sub_interval));
}
