compute_transp (const_rtx x, int indx, sbitmap *bmap, int set_p)
{
  int i, j;
  enum rtx_code code;
  const char *fmt;


 repeat:

  if (x == 0)
    return;

  code = GET_CODE (x);
  switch (code)
    {
    case REG:
      if (set_p)
	{
	  df_ref def;
	  for (def = DF_REG_DEF_CHAIN (REGNO (x));
	       def;
	       def = DF_REF_NEXT_REG (def))
	    SET_BIT (bmap[DF_REF_BB (def)->index], indx);
	}
      else
	{
	  df_ref def;
	  for (def = DF_REG_DEF_CHAIN (REGNO (x));
	       def;
	       def = DF_REF_NEXT_REG (def))
	    RESET_BIT (bmap[DF_REF_BB (def)->index], indx);
	}

      return;

    case MEM:
      if (! MEM_READONLY_P (x))
	{
	  bitmap_iterator bi;
	  unsigned bb_index;


	  EXECUTE_IF_SET_IN_BITMAP (blocks_with_calls, 0, bb_index, bi)
	    {
	      if (set_p)
		SET_BIT (bmap[bb_index], indx);
	      else
		RESET_BIT (bmap[bb_index], indx);
	    }


	    EXECUTE_IF_AND_COMPL_IN_BITMAP (modify_mem_list_set,
					    blocks_with_calls,
					    0, bb_index, bi)
	      {
		rtx list_entry = canon_modify_mem_list[bb_index];

		while (list_entry)
		  {
		    rtx dest, dest_addr;


		    dest = XEXP (list_entry, 0);
		    list_entry = XEXP (list_entry, 1);
		    dest_addr = XEXP (list_entry, 0);

		    if (canon_true_dependence (dest, GET_MODE (dest), dest_addr,
					       x, NULL_RTX, rtx_addr_varies_p))
		      {
			if (set_p)
			  SET_BIT (bmap[bb_index], indx);
			else
			  RESET_BIT (bmap[bb_index], indx);
			break;
		      }
		    list_entry = XEXP (list_entry, 1);
	          }
	      }
	}

      x = XEXP (x, 0);
      goto repeat;

    case PC:
    case CC0:
    case CONST:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_FIXED:
    case CONST_VECTOR:
    case SYMBOL_REF:
    case LABEL_REF:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
      return;

    default:
      break;
    }

  for (i = GET_RTX_LENGTH (code) - 1, fmt = GET_RTX_FORMAT (code); i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{


	  if (i == 0)
	    {
	      x = XEXP (x, i);
	      goto repeat;
	    }

	  compute_transp (XEXP (x, i), indx, bmap, set_p);
	}
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  compute_transp (XVECEXP (x, i, j), indx, bmap, set_p);
    }
}
