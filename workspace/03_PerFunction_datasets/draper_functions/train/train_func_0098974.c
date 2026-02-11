setup_tableswitch(JVM_CODE_GRAPH_NODE *val)
{
  Dlist tmp;
  int i, n;

  if(!val) {
    BAD_ARG();
    return -1;
  }

  val->op = jvm_tableswitch;

  n = val->switch_info->high - val->switch_info->low + 1;

  val->switch_info->sorted_entries =
     (JVM_SWITCH_ENTRY **)malloc(sizeof(JVM_SWITCH_ENTRY *) * n);
  if(!val->switch_info->sorted_entries) return -1;

  val->switch_info->num_entries = n;

  for(i = 0; i < n; i++)
    val->switch_info->sorted_entries[i] = NULL;


  dl_traverse(tmp, val->switch_info->offsets) {
    JVM_SWITCH_ENTRY *entry = (JVM_SWITCH_ENTRY *) tmp->val;
    int idx;

    idx = entry->case_num - val->switch_info->low;
    val->switch_info->sorted_entries[idx] = entry;
    i++;
  }


  for(i = 0; i < n; i++) {
    if(!val->switch_info->sorted_entries[i]) {
      JVM_SWITCH_ENTRY *new_entry =
         (JVM_SWITCH_ENTRY *)malloc(sizeof(JVM_SWITCH_ENTRY));

      if(!new_entry) return -1;

      new_entry->instr = val->switch_info->default_case;
      new_entry->case_num = val->switch_info->low + i;

      val->switch_info->sorted_entries[i] = new_entry;
    }
  }


  qsort(val->switch_info->sorted_entries, n, sizeof(JVM_SWITCH_ENTRY *),
     switch_entry_compare);


  val->switch_info->cell_padding = 3-(val->pc%4);
  val->width = 1 + val->switch_info->cell_padding + 12 + n * 4;

  return 0;
}
