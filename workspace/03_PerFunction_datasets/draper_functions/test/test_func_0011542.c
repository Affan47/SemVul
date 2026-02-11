load_states_file (name)
     char *name;
{
  Node *n;
  int return_seen = 0;

  yyin_name = xstrdup (name);
  linenum = 1;

  yyin = fopen (yyin_name, "r");
  if (yyin == NULL)
    {
      fprintf (stderr, _("%s: couldn't open definition file `%s': %s\n"),
	       program, yyin_name, strerror (errno));
      exit (1);
    }


  yyparse ();
  fclose (yyin);


  n = eval_statement_list (global_stmts, NULL, &return_seen);
  node_free (n);


  global_stmts = list ();
}
