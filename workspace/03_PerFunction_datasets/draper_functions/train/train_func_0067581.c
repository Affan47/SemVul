parseFilter (
	char	 *src,
	char	**head,
	char	**tail,
	int	 *ndigits)
{
  int	 i, j;

  for (i=0 ; (i<strlen(src)) && (src[i]!='X') ; i++);
  *head = (char *)malloc(i+1);
  if (*head == NULL)
  {
    printf ("Error: cannot malloc(*head), error=%d (%s)\n",
		errno, strerror (errno));
    return (-1);
  }
  strncpy (*head, src, i);
  (*head)[i] = '\0';

  for (j=i ; (i<strlen(src)) && (src[j]=='X') ; j++);
  *tail = (char *)malloc(strlen(src)-j+1);
  if (*tail == NULL)
  {
    printf ("Error: cannot malloc(*tail), error=%d (%s)\n",
		errno, strerror (errno));
    return (-1);
  }
  strcpy (*tail, &(src[j]));

  *ndigits = j-i;

  return (0);
}
