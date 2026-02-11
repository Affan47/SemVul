chop(struct header *cur)
{
  if(cur->len && cur->value[cur->len - 1] == '\n')
    cur->value[--cur->len] = '\0';
}
