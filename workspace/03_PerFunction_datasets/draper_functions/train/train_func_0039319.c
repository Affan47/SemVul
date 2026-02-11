merge_notes (rtx i1, rtx i2)
{


  rtx equiv1 = find_reg_equal_equiv_note (i1);
  rtx equiv2 = find_reg_equal_equiv_note (i2);

  if (equiv1 && !equiv2)
    remove_note (i1, equiv1);
  else if (!equiv1 && equiv2)
    remove_note (i2, equiv2);
  else if (equiv1 && equiv2
	   && !rtx_equal_p (XEXP (equiv1, 0), XEXP (equiv2, 0)))
    {
      remove_note (i1, equiv1);
      remove_note (i2, equiv2);
    }
}
