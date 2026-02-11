update_user_time(char *name, time_t the_time, char *debug_label)
{
  struct hashtab_elem *he;


  if (the_time < 0)
    {
      utmp_print_file_and_line (stdout);
      fprintf (stddebug,
               ": problem: update user %.*s (for %s) with %ld seconds?!\n",
               NAME_LEN, name, debug_label, (long) the_time);
      fatal ("Possible overflow of time_t!  Can't continue.");
    }

  if (debugging_enabled
      && ((names == NULL) || hashtab_find (names, name, (unsigned int)NAME_LEN)))
    fprintf (stddebug, "\t\t\t\t\t%*.2f %-*.*s (%s)\n",
             NAME_LEN, (double) the_time / 3600.0,
             NAME_LEN, NAME_LEN, name, debug_label);

  he = hashtab_find (user_totals, name, (unsigned int)NAME_LEN);
  if (he == NULL)
    {
      struct user_data u;

      u.time = 0;
      he = hashtab_create (user_totals, name, NAME_LEN);
      hashtab_set_value (he, &u, sizeof (u));
    }


  {
    struct user_data *u = hashtab_get_value (he);
    u->time += the_time;
  }
}
