Execute_Directive(int pl_file, int pl_line, Bool is_system, CodePtr proc)
{
  Reset_Prolog();

  if (!is_system)
    nb_user_directives++;

  if (!Call_Prolog(proc))
    fprintf(stderr,
	    ERR_DIRECTIVE_FAILED, atom_tbl[pl_file].name, pl_line,
	    (is_system) ? "system" : "user");

  Reset_Prolog();
}
