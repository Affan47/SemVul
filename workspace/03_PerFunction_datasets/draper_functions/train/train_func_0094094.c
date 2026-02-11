equal_different_set_p (rtx p1, rtx s1, rtx p2, rtx s2)
{
  int i;
  rtx e1, e2;

  if (p1 == s1 && p2 == s2)
    return true;

  if (GET_CODE (p1) != PARALLEL || GET_CODE (p2) != PARALLEL)
    return false;

  if (XVECLEN (p1, 0) != XVECLEN (p2, 0))
    return false;

  for (i = 0; i < XVECLEN (p1, 0); i++)
    {
      e1 = XVECEXP (p1, 0, i);
      e2 = XVECEXP (p2, 0, i);
      if (e1 == s1 && e2 == s2)
        continue;
      if (reload_completed
          ? rtx_renumbered_equal_p (e1, e2) : rtx_equal_p (e1, e2))
        continue;

        return false;
    }

  return true;
}
