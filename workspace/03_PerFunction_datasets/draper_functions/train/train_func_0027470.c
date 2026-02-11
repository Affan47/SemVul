handle_mpi_start_Allgather()
{
  FUNC_NAME;
  DECLARE_THREAD_ID_STR(thread_id, CUR_INDEX, CUR_THREAD_ID);

  MPI_CHANGE() pushState(CURRENT, "ST_Thread", thread_id, "STV_MPI_Allgather");
  struct ezt_mpi_comm *comm = ezt_find_communicator(CUR_INDEX, (app_ptr)GET_PARAM(CUR_EV, 1));
  int my_rank = GET_PARAM(CUR_EV, 3);
  int comm_size = GET_PARAM(CUR_EV, 2);
  int len = GET_PARAM(CUR_EV, 4);

#if 0
  int i;


  for(i=0; i<comm_size; i++){
    if(i != my_rank){
      __register_comm_info(my_rank, i, len);
    }
  }
#endif

  struct mpi_coll_msg_t* msg = __enter_coll(CUR_TIME(CUR_INDEX), mpi_coll_allgather,
					    comm, my_rank,
					    len, NULL, thread_id);

  __mpi_barrier_start_generic(msg, my_rank);
}
