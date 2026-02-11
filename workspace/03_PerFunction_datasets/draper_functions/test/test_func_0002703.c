dispose_word (w)
     WORD_DESC *w;
{
  FREE (w->word);
  ocache_free (wdcache, WORD_DESC, w);
}
