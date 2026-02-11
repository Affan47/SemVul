lam_ssi_coll_smp_barrier(MPI_Comm comm)
{
  int err;
  lam_ssi_coll_data_t *lcd = comm->c_ssi_coll_data;


  if (lcd->lcd_local_size > 1)
    if ((err = MPI_Gather(NULL, 0, MPI_BYTE, NULL, 0, MPI_BYTE,
			   0, lcd->lcd_local_comm)) != MPI_SUCCESS)
      return err;


  if (lcd->lcd_coord_comms[0] != MPI_COMM_NULL) {
    int rank, rank2;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_rank(lcd->lcd_coord_comms[0], &rank2);
    if ((err = MPI_Barrier(lcd->lcd_coord_comms[0])) != MPI_SUCCESS)
      return err;
  }


  if (lcd->lcd_local_size > 1) {
    lcd->lcd_local_comm->c_ssi_coll.lsca_bcast_optimization = 0;
    err = MPI_Bcast(NULL, 0, MPI_BYTE, 0, lcd->lcd_local_comm);
    lcd->lcd_local_comm->c_ssi_coll.lsca_bcast_optimization = 1;
    if (err != MPI_SUCCESS)
      return err;
  }

  return MPI_SUCCESS;
}
