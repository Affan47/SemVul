load_words(struct word_dic *wdic, struct lookup_context *lc)
{
  int i;
  for (i = 0; i < lc->nr; i++) {
    int yomi_index;
    yomi_index = lc->array[i]->tmp.idx;
    if (yomi_index != NO_WORD) {
      int entry_index;
      struct seq_ent *seq;
      seq = anthy_cache_get_seq_ent(&lc->array[i]->xs,
				    lc->is_reverse);
      entry_index = anthy_dic_ntohl(wdic->entry_index[yomi_index]);
      fill_dic_ent(&wdic->entry[entry_index],
		   seq,
		   &lc->array[i]->xs,
		   lc->is_reverse);
      anthy_validate_seq_ent(seq, &lc->array[i]->xs, lc->is_reverse);
    }
  }
}
