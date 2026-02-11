gen_insn (rtx insn)
{
  const char *name = XSTR (insn, 0);
  const char *p;
  int len;
  int truth = maybe_eval_c_test (XSTR (insn, 2));


  if (name[0] == 0 || name[0] == '*')
    return;

  len = strlen (name);

  if (len > max_id_len)
    max_id_len = len;

  if (truth == 0)
    ;
  else if (truth == 1)
    printf ("#define HAVE_%s 1\n", name);
  else
    {


      printf ("#define HAVE_%s (", name);
      for (p = XSTR (insn, 2); *p; p++)
	{
	  if (IS_VSPACE (*p))
	    fputs (" \\\n", stdout);
	  else
	    putchar (*p);
	}
      fputs (")\n", stdout);
    }

  obstack_grow (&obstack, &insn, sizeof (rtx));
}
