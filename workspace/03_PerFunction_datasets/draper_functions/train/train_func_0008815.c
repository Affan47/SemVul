get_number_immediate(ivl_expr_t expr)
{
      long imm = 0;
      unsigned idx;

      switch (ivl_expr_type(expr)) {
	  case IVL_EX_ULONG:
	    imm = ivl_expr_uvalue(expr);
	    break;

	  case IVL_EX_NUMBER: {
		const char*bits = ivl_expr_bits(expr);
		unsigned nbits = ivl_expr_width(expr);

		if (nbits > 8*sizeof(long)) nbits = 8*sizeof(long);
		for (idx = 0 ; idx < nbits ; idx += 1) switch (bits[idx]){
		    case '0':
		      break;
		    case '1':
		      imm |= 1L << idx;
		      break;
		    default:
		      assert(0);
		}
		if (ivl_expr_signed(expr) && bits[nbits-1]=='1' &&
		    nbits < 8*sizeof(long)) imm |= -1L << nbits;
		break;
	  }

	  default:
	    assert(0);
      }

      return imm;
}
