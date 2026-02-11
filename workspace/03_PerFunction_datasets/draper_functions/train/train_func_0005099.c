_bdf_join(int c, unsigned long *len, _bdf_list_t *list)
#else
_bdf_join(c, len, list)
int c;
unsigned long *len;
_bdf_list_t *list;
#endif
{
    unsigned long i, j;
    char *fp, *dp;

    if (list == 0 || list->used == 0)
      return 0;

    *len = 0;

    dp = list->field[0];
    for (i = j = 0; i < list->used; i++) {
        fp = list->field[i];
        while (*fp)
          dp[j++] = *fp++;
        if (i + 1 < list->used)
          dp[j++] = c;
    }
    dp[j] = 0;

    *len = j;
    return dp;
}
