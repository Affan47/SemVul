__mpi_find_p2p_message(int src __attribute__((unused)),
		       int dest,
		       int len __attribute__((unused)),
		       uint32_t tag,
		       int time_id)
{
  INIT_MPI_PROCESS_INFO(GET_PROCESS_INFO(dest), p_info);

  struct hierarchical_array* array = hierarchical_array_find(MPI_P2P_ID, GET_PROCESS_CONTAINER(dest));
  struct mpi_p2p_msg_t* msg = NULL;
  int index;


  for(index = (array->nb_items)-1; index>=0; index--) {
    msg = ITH_ITEM(index, array);

    if(((msg->src == src) || (msg->src == p_info->__MPI_ANY_SOURCE)) &&
       (msg->dest == dest) &&
       ((msg->tag == tag) || (msg->tag == p_info->__MPI_ANY_TAG)) &&
       (time_id<0 ||!msg->times[time_id])) {
      return msg;
    }
  }
  return NULL;
}
