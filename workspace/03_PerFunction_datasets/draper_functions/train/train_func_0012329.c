_read_record_list (int *flag,
                   uint16_t *record_list,
                   unsigned int *record_list_length,
                   char *arg)
{
  char *endptr;
  char *tok;
  int value;

  assert (flag);
  assert (record_list);
  assert (record_list_length);
  assert (arg);

  (*flag) = 1;
  tok = strtok (arg, " ,");
  while (tok && (*record_list_length) < IPMI_SEL_MAX_RECORD)
    {
      errno = 0;
      value = strtol (tok, &endptr, 10);

      if (errno
          || endptr[0] != '\0'
          || value < 0
          || value <= IPMI_SEL_GET_RECORD_ID_FIRST_ENTRY
          || value >= IPMI_SEL_GET_RECORD_ID_LAST_ENTRY)
        {
          fprintf (stderr, "invalid record number: %d\n", value);
          exit (1);
        }

      record_list[(*record_list_length)] = value;
      (*record_list_length)++;
      tok = strtok (NULL, " ,");
    }
}
