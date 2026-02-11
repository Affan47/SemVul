apply_change_group (void)
{
  int i;
  rtx last_validated = NULL_RTX;


  for (i = 0; i < num_changes; i++)
    {
      rtx object = changes[i].object;


      if (object == 0 || object == last_validated)
	continue;

      if (GET_CODE (object) == MEM)
	{
	  if (! memory_address_p (GET_MODE (object), XEXP (object, 0)))
	    break;
	}
      else if (insn_invalid_p (object))
	{
	  rtx pat = PATTERN (object);


	  if (GET_CODE (pat) == PARALLEL
	      && GET_CODE (XVECEXP (pat, 0, XVECLEN (pat, 0) - 1)) == CLOBBER
	      && asm_noperands (PATTERN (object)) < 0)
	    {
	      rtx newpat;

	      if (XVECLEN (pat, 0) == 2)
		newpat = XVECEXP (pat, 0, 0);
	      else
		{
		  int j;

		  newpat
		    = gen_rtx_PARALLEL (VOIDmode,
					rtvec_alloc (XVECLEN (pat, 0) - 1));
		  for (j = 0; j < XVECLEN (newpat, 0); j++)
		    XVECEXP (newpat, 0, j) = XVECEXP (pat, 0, j);
		}


	      validate_change (object, &PATTERN (object), newpat, 1);
	      continue;
	    }
	  else if (GET_CODE (pat) == USE || GET_CODE (pat) == CLOBBER)


	    continue;
	  else
	    break;
	}
      last_validated = object;
    }

  if (i == num_changes)
    {
      basic_block bb;

      for (i = 0; i < num_changes; i++)
	if (changes[i].object
	    && INSN_P (changes[i].object)
	    && (bb = BLOCK_FOR_INSN (changes[i].object)))
	  bb->flags |= BB_DIRTY;

      num_changes = 0;
      return 1;
    }
  else
    {
      cancel_changes (0);
      return 0;
    }
}
