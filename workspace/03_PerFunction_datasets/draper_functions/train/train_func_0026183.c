ghw_disp_hie (struct ghw_handler *h, struct ghw_hie *top)
{
  int i;
  int indent;
  struct ghw_hie *hie;
  struct ghw_hie *n;

  hie = top;
  indent = 0;

  while (1)
    {
      for (i = 0; i < indent; i++)
	fputc (' ', stdout);
      printf ("%s", ghw_get_hie_name (hie));

      switch (hie->kind)
	{
	case ghw_hie_design:
	case ghw_hie_block:
	case ghw_hie_generate_if:
	case ghw_hie_generate_for:
	case ghw_hie_instance:
	case ghw_hie_process:
	case ghw_hie_package:
	  if (hie->name)
	    printf (" %s", hie->name);
	  if (hie->kind == ghw_hie_generate_for)
	    {
	      printf ("(");
	      ghw_disp_value (hie->u.blk.iter_value, hie->u.blk.iter_type);
	      printf (")");
	    }
	  n = hie->u.blk.child;
	  if (n == NULL)
	    n = hie->brother;
	  else
	    indent++;
	  break;
	case ghw_hie_generic:
	case ghw_hie_eos:
	  abort ();
	case ghw_hie_signal:
	case ghw_hie_port_in:
	case ghw_hie_port_out:
	case ghw_hie_port_inout:
	case ghw_hie_port_buffer:
	case ghw_hie_port_linkage:
	  {
	    unsigned int *sigs;

	    printf (" %s: ", hie->name);
	    ghw_disp_typename (h, hie->u.sig.type);
	    for (sigs = hie->u.sig.sigs; *sigs != 0; sigs++)
	      printf (" #%u", *sigs);
	    n = hie->brother;
	  }
	  break;
	default:
	  abort ();
	}
      printf ("\n");

      while (n == NULL)
	{
	  if (hie->parent == NULL)
	    return;
	  hie = hie->parent;
	  indent--;
	  n = hie->brother;
	}
      hie = n;
    }
}
