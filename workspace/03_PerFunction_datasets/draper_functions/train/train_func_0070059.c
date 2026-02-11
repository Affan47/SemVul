longest_string_in_plist(Plist p)
{
  if (p == NULL)
    return -1;
  else {
    int n1 = strlen(p->v);
    int n2 = longest_string_in_plist(p->next);
    return IMAX(n1,n2);
  }
}
