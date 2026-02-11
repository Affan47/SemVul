gang_scan(void *p, int offset, const char *key, const char *n)
{
  struct gang_scan_context *gsc = p;
  struct gang_elm *elm;
  int r;
  (void)offset;
  while (1) {
    if (gsc->nth >= gsc->nr) {
      return 0;
    }
    elm = gsc->array[gsc->nth];
    r = strcmp(elm->key, key);
    if (r == 0) {

      load_word(&elm->xs, n, 0);

      return 0;
    } else if (r > 0) {

      return 0;
    } else {

      gsc->nth ++;
    }
  }
  return 0;
}
