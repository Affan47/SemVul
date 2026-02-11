write_usracct_file(char *filename)
{
  struct hashtab_order ho;
  struct hashtab_elem *he;
  FILE *fp = NULL;


  char *s = (char *) alloca (sizeof (char) * (strlen (filename) + 2));
  (void)sprintf (s, "%s~", filename);

  if ((fp = file_open (s, 1)) == NULL)
    exit(EXIT_FAILURE);


  for (he = hashtab_first (user_table, &ho);
       he != NULL;
       he = hashtab_next (&ho))
    {
      char *name = hashtab_get_key (he);
      struct user_data *ud = hashtab_get_value (he);
      struct usracct ua;

      strncpy (ua.name, name, NAME_LEN);
      memcpy (&(ua.s), &(ud->s), sizeof (ua.s));

      if (fwrite (&ua, sizeof (ua), 1, fp) == 0)
        {
          printf ("%s (write_usracct_file): probs writing to file `%s'\n",
                  program_name, s);
          exit(EXIT_FAILURE);
        }
    }

  if (rename (s, filename) != 0)
    {
      perror ("sa");
      exit(EXIT_FAILURE);
    }
}
