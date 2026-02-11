eq(const Item *item, bool binary_cmp) const
{
  const Item_func_utc_extract *utc_func_item;

  if (this == item)
    return true;

  if (item->type() != FUNC_ITEM ||
      functype() != ((Item_func *)item)->functype())
    return false;

  utc_func_item= (const Item_func_utc_extract *) item;

  if (utc_func_item->m_extract_spec != m_extract_spec)
    return false;

  return args[0]->eq(utc_func_item->args[0], binary_cmp);
}
