_bdf_shift(unsigned long n, _bdf_list_t *list)
#else
_bdf_shift(n, list)
unsigned long n;
_bdf_list_t *list;
#endif
{
    unsigned long i, u;

    if (list == 0 || list->used == 0 || n == 0)
      return;

    if (n >= list->used) {
        list->used = 0;
        return;
    }
    for (u = n, i = 0; u < list->used; i++, u++)
      list->field[i] = list->field[u];
    list->used -= n;
}
