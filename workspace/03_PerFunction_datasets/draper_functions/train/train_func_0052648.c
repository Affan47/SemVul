Get_chk_log_entries_reverse(int                 sim_handle,
				int                 chk_handle,
				int                 num_entries,
				Output_log_struct  *entries)
{
  int i;
  int isim;
  int count;
  int return_status = REG_SUCCESS;
  Sim_entry_type *sim;

  if(!entries) return REG_FAILURE;

  if((isim = Sim_index_from_handle(sim_handle)) != -1){

    sim = &(Sim_table.sim[isim]);
    count = 0;

    for(i=(sim->Chk_log.num_entries - 1); i>=0; i--){

      if(sim->Chk_log.entry[i].chk_handle == chk_handle){

	Get_log_entry_details(&(sim->Params_table),
			      &(sim->Chk_log.entry[i]),
			      &(entries[count]));

	count++;
	if (count >= num_entries) break;
      }
    }
  }
  else{

    return_status = REG_FAILURE;
  }

  return return_status;
}
