fixup_missed_word(struct extract_stat *es, char *buf)
{
  int i;
  char *c = get_indep_part(buf);
  if (!c) {
    return ;
  }
  for (i = 0; i < es->nr; i++) {
    if (!strcmp(es->info[i].indep, c)) {
      es->info[i].valid = 0;
    }
  }
}
