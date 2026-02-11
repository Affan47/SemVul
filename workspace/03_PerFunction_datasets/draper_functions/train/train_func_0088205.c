compute_transp (const_rtx x, int indx, sbitmap *bmap)
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
	{
	  df_ref def;
	  for (def = DF_REG_DEF_CHAIN (REGNO (x));
	       def;
	       def = DF_REF_NEXT_REG (def))
	    bitmap_clear_bit (bmap[DF_REF_BB (def)->index], indx);
	}

      return;

    case MEM:
      if (! MEM_READONLY_P (x))
	{
	  bitmap_iterator bi;
	  unsigned bb_index;
	  rtx x_addr;

	  x_addr = get_addr (XEXP (x, 0));
	  x_addr = canon_rtx (x_addr);


	  EXECUTE_IF_SET_IN_BITMAP (blocks_with_calls, 0, bb_index, bi)
	    {
	      bitmap_clear_bit (bmap[bb_index], indx);
	    }


	  EXECUTE_IF_AND_COMPL_IN_BITMAP (modify_mem_list_set,
					  blocks_with_calls,
					  0, bb_index, bi)
	    {
	      vec<modify_pair> list
		= canon_modify_mem_list[bb_index];
	      modify_pair *pair;
	      unsigned ix;

	      FOR_EACH_VEC_ELT_REVERSE (list, ix, pair)
		{
		  rtx dest = pair->dest;
		  rtx dest_addr = pair->dest_addr;

		  if (canon_true_dependence (dest, GET_MODE (dest),
					     dest_addr, x, x_addr))
		    bitmap_clear_bit (bmap[bb_index], indx);
	        }
	    }
	}

      x = XEXP (x, 0);
      goto repeat;

    case PC:
    case CC0:
    case CONST:
    CASE_CONST_ANY:
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

	  compute_transp (XEXP (x, i), indx, bmap);
	}
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  compute_transp (XVECEXP (x, i, j), indx, bmap);
    }
}
