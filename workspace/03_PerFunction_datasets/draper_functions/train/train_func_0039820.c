i2list_append(I2list lst, int i, int j)
{
  if (lst == NULL) {
    I2list g = get_i2list();
    g->i = i;
    g->j = j;
    g->next = NULL;
    return g;
  }
  else {
    lst->next = i2list_append(lst->next, i, j);
    return lst;
  }
}
