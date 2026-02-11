match_arg (prim_name, type, argp, env, filename, linenum)
     char *prim_name;
     NodeType type;
     ListItem **argp;
     Environment *env;
     char *filename;
     unsigned int linenum;
{
  ListItem *arg = *argp;
  Node *n;

  NEED_ARG ();
  n = eval_expr ((Expr *) arg->data, env);
  if (type != nVOID && n->type != type)
    {
      fprintf (stderr, _("%s:%d: %s: illegal argument type\n"),
	       filename, linenum, prim_name);
      exit (1);
    }
  *argp = arg->next;

  return n;
}
