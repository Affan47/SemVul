anthy_trie_find_prefix(struct text_trie *tt, const char *str,
		       char *buf, int buf_len,
		       int (*cb)(const char *key, const char *str))
{
  if (!tt || tt->fatal) {
    return ;
  }
  anthy_priv_dic_lock();
  trie_find_prefix(tt, str, buf, buf_len, cb);
  anthy_priv_dic_unlock();
  purge_cache(tt);
}
