distrib_default_value_new(uint32_t weight, char * group_pattern, char * value)
{
  struct newsnntp_distrib_default_value * n;

  n = malloc(sizeof(* n));
  if (n == NULL)
    return NULL;

  n->dst_group_pattern = strdup(group_pattern);
  if (n->dst_group_pattern == NULL) {
    free(n);
    return NULL;
  }

  n->dst_value = strdup(value);
  if (n->dst_value == NULL) {
    free(n->dst_group_pattern);
    free(n);
    return NULL;
  }

  n->dst_weight = weight;

  return n;
}
