log_out(struct utmp *entry)
{
  struct hashtab_elem *he;

  if (entry->ut_line[0] == '\0')
    {
      if (print_file_problems)
        {
          utmp_print_file_and_line (stddebug);
          (void)fprintf (stddebug,
                         ": problem: trying to hash rec with ut_line == NULL\n");
        }
      return;
    }


  he = hashtab_find (login_table, entry->ut_line, (unsigned int)TTY_LEN);

  if (he != NULL)
    {
      struct login_data *l = hashtab_get_value (he);

      update_user_time (l->ut_name, entry->ut_time - l->time, "logout");

      hashtab_delete (he);
    }
  else
    {


      if (print_file_problems)
        {
          utmp_print_file_and_line (stddebug);
          fprintf (stddebug, ": problem: missing login record for `%.*s'\n",
                   TTY_LEN, entry->ut_line);
        }
    }
}
