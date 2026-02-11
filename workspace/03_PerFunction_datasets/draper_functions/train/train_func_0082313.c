find_wttab(struct wttable *array, const char *name)
{
  struct wttable *w;
  for (w = array; w->name; w++) {
    if (!strcmp(w->name, name)) {
      return w;
    }
  }
  return NULL;
}
