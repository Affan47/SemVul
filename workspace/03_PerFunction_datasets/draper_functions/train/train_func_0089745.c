ira_initiate_emit_data (void)
{
  ira_allocno_t a;
  ira_allocno_iterator ai;

  ira_allocno_emit_data
    = (ira_emit_data_t) ira_allocate (ira_allocnos_num
				      * sizeof (struct ira_emit_data));
  memset (ira_allocno_emit_data, 0,
	  ira_allocnos_num * sizeof (struct ira_emit_data));
  FOR_EACH_ALLOCNO (a, ai)
    ALLOCNO_ADD_DATA (a) = ira_allocno_emit_data + ALLOCNO_NUM (a);
  new_allocno_emit_data_vec.create (50);

}
