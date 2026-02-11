reg_set_to_hard_reg_set (HARD_REG_SET *to, const_bitmap from)
{
  unsigned i;
  bitmap_iterator bi;

  EXECUTE_IF_SET_IN_BITMAP (from, 0, i, bi)
    {
      if (i >= FIRST_PSEUDO_REGISTER)
	return;
      SET_HARD_REG_BIT (*to, i);
    }
}
