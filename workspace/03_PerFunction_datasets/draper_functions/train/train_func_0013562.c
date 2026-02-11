marked_for_renaming (tree sym)
{
  if (!symbols_to_rename_set || sym == NULL_TREE)
    return false;
  return bitmap_bit_p (symbols_to_rename_set, DECL_UID (sym));
}
