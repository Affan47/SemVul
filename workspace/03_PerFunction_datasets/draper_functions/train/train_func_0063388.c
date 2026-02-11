_get_answer (char *answer)
{
  char *tmp = malloc (KNOCKER_CONF_MAX_LEN);


  fscanf (stdin, "%s", tmp);

  if (answer == NULL)
    answer = malloc (strlen (tmp) + 1);
  else
    answer = realloc (answer, strlen (tmp) + 1);

  strcpy (answer, tmp);
  free (tmp);

  return answer;
}
