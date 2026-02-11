write_table (const definition * def)
{
  version_list *vp;
  proc_list *proc;
  int current;
  int expected;
  char progvers[100];
  int warning;

  for (vp = def->def.pr.versions; vp != NULL; vp = vp->next)
    {
      warning = 0;
      s_print (progvers, "%s_%s",
	       locase (def->def_name), vp->vers_num);

      f_print (fout, tbl_hdr, progvers);

      if (nullproc (vp->procs))
	{
	  expected = 0;
	}
      else
	{
	  expected = 1;
	  f_print (fout, null_entry);
	}
      for (proc = vp->procs; proc != NULL; proc = proc->next)
	{
	  current = atoi (proc->proc_num);
	  if (current != expected++)
	    {
	      f_print (fout,
		       "\n/*\n * WARNING: table out of order\n */\n");
	      if (warning == 0)
		{
		  f_print (stderr,
			   "WARNING %s table is out of order\n",
			   progvers);
		  warning = 1;
		  nonfatalerrors = 1;
		}
	      expected = current + 1;
	    }
	  f_print (fout, "\n\t(char *(*)())RPCGEN_ACTION(");


	  if (Cflag && !newstyle)
	    pvname_svc (proc->proc_name, vp->vers_num);
	  else
	    {
	      if (newstyle)
		f_print (fout, "_");
	      pvname (proc->proc_name, vp->vers_num);
	    }
	  f_print (fout, "),\n");


	  if (proc->arg_num > 1)
	    printit ((char *) NULL, proc->args.argname);
	  else

	    printit (proc->args.decls->decl.prefix,
		     proc->args.decls->decl.type);

	  printit (proc->res_prefix, proc->res_type);
	}


      f_print (fout, tbl_end);
      f_print (fout, tbl_nproc, progvers, progvers, progvers);
    }
}
