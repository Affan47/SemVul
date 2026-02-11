_dmalloc_table_insert(mem_table_t *mem_table, const int entry_n,
			      const char *file, const unsigned int line,
			      const unsigned long size, int *entry_cp)
{
  unsigned int	bucket;
  mem_table_t	*tab_p, *tab_end_p, *tab_bounds_p, *tab_other_p;

  bucket = which_bucket(entry_n, file, line);
  tab_p = mem_table + bucket;


  tab_end_p = tab_p;
  tab_other_p = mem_table + entry_n - 1;

  tab_bounds_p = tab_other_p;

  while (1) {
    if (tab_p->mt_file == file && tab_p->mt_line == line) {

      break;
    }
    else if (tab_p->mt_file == NULL) {

      break;
    }
    tab_p++;
    if (tab_p == tab_bounds_p) {
      tab_p = mem_table;
    }

    if (tab_p == tab_end_p) {
    }
  }


  if (tab_p->mt_file == NULL) {

    if (*entry_cp >= MEMORY_TABLE_SIZE) {

      tab_p = tab_other_p;
    }
    else {

      tab_p->mt_file = file;
      tab_p->mt_line = line;

      tab_p->mt_entry_pos_p = tab_p;
      (*entry_cp)++;
    }
  }


  tab_p->mt_total_size += size;
  tab_p->mt_total_c++;
  tab_p->mt_in_use_size += size;
  tab_p->mt_in_use_c++;
}
