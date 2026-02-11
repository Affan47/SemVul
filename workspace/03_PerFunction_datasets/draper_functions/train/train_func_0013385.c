cp_check_qualified_type (const_tree cand, const_tree base, int type_quals,
			 cp_ref_qualifier rqual, tree raises)
{
  return (check_qualified_type (cand, base, type_quals)
	  && comp_except_specs (raises, TYPE_RAISES_EXCEPTIONS (cand),
				ce_exact)
	  && type_memfn_rqual (cand) == rqual);
}
