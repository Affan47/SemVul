__print_p2p_message(FILE *stream, struct mpi_p2p_msg_t *msg)
{
  fprintf(stream, "%d\t%d\t%d\t%x",
	  msg->src, msg->dest, msg->len, msg->tag);
  int i;
  for(i=0; i<P2P_NB_TIMES; i++)
    fprintf(stream, "\t%lld", msg->times[i]);

  fprintf(stream, "\t%p\t%p", msg->sender_request, msg->recver_request);
  fprintf(stream, "\n");
}
