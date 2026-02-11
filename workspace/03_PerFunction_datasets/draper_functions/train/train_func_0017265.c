check_user_alignment (const_tree align, bool allow_zero)
{
  int i;

  if (TREE_CODE (align) != INTEGER_CST
      || !INTEGRAL_TYPE_P (TREE_TYPE (align)))
    {
      error ("requested alignment is not an integer constant");
      return -1;
    }
  else if (allow_zero && integer_zerop (align))
    return -1;
  else if ((i = tree_log2 (align)) == -1)
    {
      error ("requested alignment is not a power of 2");
      return -1;
    }
  else if (i >= HOST_BITS_PER_INT - BITS_PER_UNIT_LOG)
    {
      error ("requested alignment is too large");
      return -1;
    }
  return i;
}
