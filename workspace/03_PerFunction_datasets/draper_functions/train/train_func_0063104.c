write_nettype_register (const char *transp)
{
  list *l;
  definition *def;
  version_list *vp;

  for (l = defined; l != NULL; l = l->next)
    {
      def = (definition *) l->val;
      if (def->def_kind != DEF_PROGRAM)
	{
	  continue;
	}
      for (vp = def->def.pr.versions; vp != NULL; vp = vp->next)
	{
	  f_print (fout, "\tif (!svc_create (");
	  pvname (def->def_name, vp->vers_num);
	  f_print (fout, ", %s, %s, \"%s\")) {\n ",
		   def->def_name, vp->vers_name, transp);
	  (void) sprintf (_errbuf,
			  "unable to create (%s, %s) for %s.",
			  def->def_name, vp->vers_name, transp);
	  print_err_message ("\t\t");
	  f_print (fout, "\t\texit (1);\n");
	  f_print (fout, "\t}\n");
	}
    }
}
