tsin_remove_last()
{
  if (!tss.c_len)
    return;
  tss.c_len--;
  tss.c_idx--;
}
