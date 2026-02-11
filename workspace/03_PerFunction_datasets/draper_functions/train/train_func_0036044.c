font_entry_hash_qcmp (struct font_entry ** x, struct font_entry ** y)
{
  return_STRING_COMPARE ((*x)->key, (*y)->key);
}
