firstitem(struct llist* p)


{
  if (p == NULL) {
    return(NULL);
  };
  p->place = p->first;
  if (p->place == NULL) {
    return(NULL);
  } else {
    return(p->place->datum);
  };
}
