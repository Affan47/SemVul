insert_type (char **argv, int *arg_ptr,
	     const struct parser_table *entry,
	     PRED_FUNC which_pred)
{
  mode_t type_cell;
  struct predicate *our_pred;
  float rate = 0.5;
  const char *typeletter;

  if (collect_arg(argv, arg_ptr, &typeletter))
    {
      if (strlen(typeletter) != 1u)
	{
	  error(1, 0, _("Arguments to -type should contain only one letter"));
	  return false;
	}

      switch (typeletter[0])
	{
	case 'b':
	  type_cell = S_IFBLK;
	  rate = 0.01f;
	  break;
	case 'c':
	  type_cell = S_IFCHR;
	  rate = 0.01f;
	  break;
	case 'd':
	  type_cell = S_IFDIR;
	  rate = 0.4f;
	  break;
	case 'f':
	  type_cell = S_IFREG;
	  rate = 0.95f;
	  break;
#ifdef S_IFLNK
	case 'l':
	  type_cell = S_IFLNK;
	  rate = 0.1f;
	  break;
#endif
#ifdef S_IFIFO
	case 'p':
	  type_cell = S_IFIFO;
	  rate = 0.01f;
	  break;
#endif
#ifdef S_IFSOCK
	case 's':
	  type_cell = S_IFSOCK;
	  rate = 0.01f;
	  break;
#endif
#ifdef S_IFDOOR
	case 'D':
	  type_cell = S_IFDOOR;
	  rate = 0.01f;
	  break;
#endif
	default:
	  error(1, 0, _("Unknown argument to -type: %c"), (*typeletter));
	  return false;
	}
      our_pred = insert_primary_withpred (entry, which_pred);
      our_pred->est_success_rate = rate;


      if (which_pred == pred_xtype)
	{
	  our_pred->need_stat = true;
	  our_pred->need_type = false;
	}
      else
	{
	  our_pred->need_stat = false;
	  our_pred->need_type = true;
	}
      our_pred->args.type = type_cell;
      return true;
    }
  return false;
}
