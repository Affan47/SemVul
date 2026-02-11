XOTclReverseClasses(XOTclClasses *sl) {
  XOTclClasses *first = NULL;
  for (; sl; sl = sl->next) {
    XOTclClasses *element = NEW(XOTclClasses);
    element->cl = sl->cl;
    element->clientData = sl->clientData;
    element->next = first;
    first = element;
  }
  return first;
}
