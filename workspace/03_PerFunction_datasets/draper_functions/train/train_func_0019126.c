display_frame_expr (char *hdr, SCM exp, char *tlr, int indentation, SCM sport, SCM port, scm_print_state *pstate)
{
  int i = 0, n;
  scm_t_ptob_descriptor *ptob = scm_ptobs + SCM_PTOBNUM (sport);
  do
    {
      pstate->length = print_params[i].length;
      ptob->seek (sport, 0, SEEK_SET);
      if (scm_is_pair (exp))
	{
	  pstate->level = print_params[i].level - 1;
	  scm_iprlist (hdr, exp, tlr[0], sport, pstate);
	  scm_puts (&tlr[1], sport);
	}
      else
	{
	  pstate->level = print_params[i].level;
	  scm_iprin1 (exp, sport, pstate);
	}
      ptob->flush (sport);
      n = ptob->seek (sport, 0, SEEK_CUR);
      ++i;
    }
  while (indentation + n > SCM_BACKTRACE_WIDTH && i < n_print_params);
  ptob->truncate (sport, n);

  scm_display (scm_strport_to_string (sport), port);
}
