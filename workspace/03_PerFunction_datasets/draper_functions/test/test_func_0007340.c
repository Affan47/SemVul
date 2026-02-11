lookup(const char *word) const
{
    struct hentry * dp;
    if (tableptr) {
       dp = tableptr[hash(word)];
       if (!dp) return NULL;
       for (  ;  dp != NULL;  dp = dp->next) {
          if (strcmp(word, dp->word) == 0) return dp;
       }
    }
    return NULL;
}
