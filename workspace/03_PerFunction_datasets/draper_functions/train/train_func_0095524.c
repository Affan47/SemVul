parse_fstype (const struct parser_table* entry, char **argv, int *arg_ptr)
{
  const char *typename;
  if (collect_arg(argv, arg_ptr, &typename))
    {
      struct predicate *our_pred = insert_primary (entry);
      our_pred->args.str = typename;


      our_pred->est_success_rate = estimate_fstype_success_rate(typename);
      return true;
    }
  else
    {
      return false;
    }
}
