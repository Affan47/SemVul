find_pseudo_copy (rtx set)
{
  rtx dest = SET_DEST (set);
  rtx src = SET_SRC (set);
  unsigned int rd, rs;
  bitmap b;

  if (!REG_P (dest) || !REG_P (src))
    return false;

  rd = REGNO (dest);
  rs = REGNO (src);
  if (HARD_REGISTER_NUM_P (rd) || HARD_REGISTER_NUM_P (rs))
    return false;

  b = reg_copy_graph[rs];
  if (b == NULL)
    {
      b = BITMAP_ALLOC (NULL);
      reg_copy_graph[rs] = b;
    }

  bitmap_set_bit (b, rd);

  return true;
}
