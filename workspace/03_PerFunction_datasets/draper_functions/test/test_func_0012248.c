join_init_read_record(JOIN_TAB *tab)
{
  if (tab->select && tab->select->quick && tab->select->quick->reset())
    return 1;
  init_read_record(&tab->read_record, tab->join->thd, tab->table,
		   tab->select,1,1, FALSE);
  return (*tab->read_record.read_record)(&tab->read_record);
}
