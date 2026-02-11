execute_commands (current, rel_dep, q, made_key)
     struct rules *current;
     char *rel_dep;
     DepQ *q;
     BKey *made_key;
{
  register struct cmds *curcmd;
  char *expcmd, x_command[MAXCMDLENGTH], fname[MYMAXNAMLEN],
       command_processor[MYMAXNAMLEN];

  if (rel_dep)
    strcpy (fname, rel_dep);

  if (current)
    curcmd = current->cmdlist;

  if (curcmd) {
    restore_all_vers ();
    strcpy (command_processor, expandmacro ("$(SHELL)"));
    while (curcmd) {
      if (curcmd->command) {
	no_comm_subst = TRUE;
	strcpy (x_command, expandmacro (curcmd->command));
	no_comm_subst = FALSE;
	if ((expcmd = malloc (MAXCMDLENGTH)) == NIL)
	  errexit(10,"malloc");
	strcpy (expcmd, expand_command (x_command, current, fname));
	execute (expcmd, command_processor);
	free (expcmd);
      }
      else
	break;
      curcmd = curcmd->nextcmd;
    }

    if (simple_done) {
      mark_all_done (current);
      simple_done = FALSE;
    }
    save_targets (current, fname, q, made_key, touch_time);
  }

  cleanup_links (link_reg);
  free_linklist ();
  link_reg = (struct linkreg *) NIL;

  return TRUE;
}
