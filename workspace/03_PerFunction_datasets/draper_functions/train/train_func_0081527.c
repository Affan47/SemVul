Perl_amagic_is_enabled(pTHX_ int method)
{
      SV *lex_mask = cop_hints_fetch_pvs(PL_curcop, "overloading", 0);

      assert(PL_curcop->cop_hints & HINT_NO_AMAGIC);

      if ( !lex_mask || !SvOK(lex_mask) )

	  return FALSE;
      else if ( lex_mask && SvPOK(lex_mask) ) {


	  STRLEN len;
	  const int offset = method / 8;
	  const int bit    = method % 8;
	  char *pv = SvPV(lex_mask, len);


	  if ( (STRLEN)offset < len && pv[offset] & ( 1 << bit ) )
	      return FALSE;
      }
      return TRUE;
}
