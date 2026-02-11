parse_inum (const struct parser_table* entry, char **argv, int *arg_ptr)
{
  struct predicate *p =  insert_num (argv, arg_ptr, entry);
  if (p)
    {


      p->est_success_rate = 1e-6;
      return true;
    }
  else
    {
      return false;
    }
}
