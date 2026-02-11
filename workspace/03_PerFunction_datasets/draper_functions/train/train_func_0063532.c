parseInit(void)
{
  Parser * new;
  new = (Parser*)malloc(sizeof(Parser));
  if ( new == NULL )
    return NULL;
  bzero(new, sizeof(Parser));
  new->next = NULL;
  return new;
}
