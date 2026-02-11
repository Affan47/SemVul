print_hidden_TokenList( TokenList *list, char *sep )

{

  TokenList *i_tl;

  i_tl = list;
  if (NULL!=i_tl) {
    printf("%s", i_tl->item);
    i_tl = i_tl->next;
  } else {
    printf("empty");
  }

  while (NULL != i_tl) {
    printf("%s%s", sep, i_tl->item);
    i_tl = i_tl->next;
  }

}
