get_text_align_nop_count (offsetT fill_size, bfd_boolean use_no_density)
{
  int count = 0;

  if (use_no_density)
    {
      gas_assert (fill_size % 3 == 0);
      return (fill_size / 3);
    }

  gas_assert (fill_size != 1);

  while (fill_size > 1)
    {
      int insn_size = 3;
      if (fill_size == 2 || fill_size == 4)
	insn_size = 2;
      fill_size -= insn_size;
      count++;
    }
  gas_assert (fill_size != 1);
  return count;
}
