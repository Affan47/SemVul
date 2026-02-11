lam_ssi_coll_shmem_init(MPI_Comm comm,
			const lam_ssi_coll_actions_1_1_0_t **new_actions)
{
  int i;
  lam_ssi_coll_data_t *lcd;


  comm->c_ssi_coll_data = local_coll_data;
  lcd = comm->c_ssi_coll_data;
  lcd->lcd_segment_in_use = 0;


  lcd->lcd_num_cpus = lam_ssi_coll_shmem_get_num_cpu();


  lcd->lcd_shared_control_base = lcd->lcd_shared_segment_base;
  lcd->lcd_shared_message_pool_base = lcd->lcd_shared_segment_base
    + lcd->lcd_control_segment_size;


  lcd->lcd_barrier[0] = (int*) (lcd->lcd_shared_control_base);
  lcd->lcd_collective_track[0] = (int*)
    ((char*)lcd->lcd_barrier[0] + lcd->lcd_num_procs* CACHELINESIZE);

  for (i = 1; i < lcd->lcd_num_segments + 1; ++i) {
    lcd->lcd_barrier[i] = (int*)
      ((char*)lcd->lcd_collective_track[i - 1] +
       lcd->lcd_num_procs* CACHELINESIZE);
    lcd->lcd_collective_track[i] = (int*)
      ((char*)lcd->lcd_barrier[i] + lcd->lcd_num_procs* CACHELINESIZE);
  }

  for (i = 0; i < lcd->lcd_num_segments; ++i) {
    lcd->lcd_message_segment[i] = lcd->lcd_shared_message_pool_base +
      i * (lcd->lcd_message_pool_size / lcd->lcd_num_segments);
  }


  *new_actions = &shmem_functions;


  if (lam_ssi_coll_verbose >= 10) {
    lam_debug(lam_ssi_coll_did, "shmem: init communicator %s", comm->c_name);
  }


  lam_debug(lam_ssi_coll_did, "shmem: done initializing %s", comm->c_name);
  return 0;
}
