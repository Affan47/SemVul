dump_lattice_value (FILE *outf, const char *prefix, prop_value_t val)
{
  switch (val.lattice_val)
    {
    case UNINITIALIZED:
      fprintf (outf, "%sUNINITIALIZED", prefix);
      break;
    case UNDEFINED:
      fprintf (outf, "%sUNDEFINED", prefix);
      break;
    case VARYING:
      fprintf (outf, "%sVARYING", prefix);
      break;
    case CONSTANT:
      fprintf (outf, "%sCONSTANT ", prefix);
      if (TREE_CODE (val.value) != INTEGER_CST
	  || double_int_zero_p (val.mask))
	print_generic_expr (outf, val.value, dump_flags);
      else
	{
	  double_int cval = double_int_and_not (tree_to_double_int (val.value),
						val.mask);
	  fprintf (outf, "%sCONSTANT " HOST_WIDE_INT_PRINT_DOUBLE_HEX,
		   prefix, cval.high, cval.low);
	  fprintf (outf, " (" HOST_WIDE_INT_PRINT_DOUBLE_HEX ")",
		   val.mask.high, val.mask.low);
	}
      break;
    default:
      gcc_unreachable ();
    }
}
