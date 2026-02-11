write_stubs (void)
{
  list *l;
  definition *def;

  fprintf (fout,
	   "\n/* Default timeout can be changed using clnt_control() */\n");
  fprintf (fout, "static struct timeval TIMEOUT = { %d, 0 };\n",
	   DEFAULT_TIMEOUT);
  for (l = defined; l != NULL; l = l->next)
    {
      def = (definition *) l->val;
      if (def->def_kind == DEF_PROGRAM)
	{
	  write_program (def);
	}
    }
}
