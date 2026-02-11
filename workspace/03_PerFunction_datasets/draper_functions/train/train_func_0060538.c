xsh_arclist_free(xsh_arclist** list)
{
  int i;

  if (list && *list) {
    if ((*list)->list) {
      for (i=0; i< (*list)->size; i++) {
        xsh_arcline* arc = (*list)->list[i];
        xsh_arcline_free(&arc);
      }
      cpl_free((*list)->list);
      xsh_free_propertylist(&((*list)->header));
    }
    XSH_FREE((*list)->rejected);
    cpl_free(*list);
    *list = NULL;
  }
}
