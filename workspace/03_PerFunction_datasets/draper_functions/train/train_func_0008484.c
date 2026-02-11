ShowList(tLinkedList *l)
{
  int first = 1;

  while (l != NULL) {
    if (!first) printf(", ");
    if (l->Value != NULL) printf("%s", l->Value);
    l = l->next;
    first = 0;
  }
}
