append_strings_to_vector (char **vector_0, char *string,
			  char const *delimiter_class)
{
  char **vector;
  if (vector_0)
    {
      int length = vector_length (vector_0);
      vector_0 = xnrealloc (vector_0, length + 2 + strlen (string) / 2,
			    sizeof *vector_0);
      vector = &vector_0[length];
    }
  else
    vector = vector_0 = xnmalloc (2 + strlen (string) / 2, sizeof *vector);

  do
    *vector = strsep (&string, delimiter_class);
  while (*vector++);
  return xnrealloc (vector_0, vector - vector_0, sizeof *vector_0);
}
