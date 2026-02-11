clear_record(struct record_stat* rst)
{
  struct record_section *rsc;
  for (rsc = rst->section_list.next; rsc; rsc = rsc->next) {
    trie_remove_all(&rsc->cols, &rsc->lru_nr_used, &rsc->lru_nr_sused);
  }
  rst->cur_row = NULL;
}
