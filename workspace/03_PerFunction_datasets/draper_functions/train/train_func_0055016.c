appendArtHolder (ArtHolder artH, ArtHolder *head, u_int *count)
{
  ArtHolder p ;

  ASSERT (head != NULL) ;
  ASSERT (count != NULL) ;

  for (p = *head ; p != NULL && p->next != NULL ; p = p->next)
     ;

  if (p == NULL)
    *head = artH ;
  else
    p->next = artH ;

  artH->next = NULL ;
  (*count)++ ;
}
