distrib_value_meaning_new(char * value, char * meaning)
{
  struct newsnntp_distrib_value_meaning * n;

  n = malloc(sizeof(* n));

  if (n == NULL)
    return NULL;

  n->dst_value = strdup(value);
  if (n->dst_value == NULL) {
    free(n);
    return NULL;
  }

  n->dst_meaning = strdup(meaning);
  if (n->dst_meaning == NULL) {
    free(n->dst_value);
    free(n);
    return NULL;
  }

  return n;
}
