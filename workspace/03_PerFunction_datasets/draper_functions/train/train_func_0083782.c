__new_pers_req(enum mpi_request_type type,
				      app_ptr buffer,
				      int src,
				      int dest,
				      int len,
				      int tag,
				      app_ptr mpi_req)
{
  struct mpi_pers_req_t* req = NULL;
  if(type == mpi_req_recv) {
    req = hierarchical_array_new_item(GET_PROCESS_CONTAINER(dest), MPI_PERS_ID);
    req->mpi_req = __mpi_new_mpi_request(dest, mpi_req, type);
  } else {
    req = hierarchical_array_new_item(GET_PROCESS_CONTAINER(src), MPI_PERS_ID);
    req->mpi_req = __mpi_new_mpi_request(src, mpi_req, type);
  }

  req->type = type;
  req->buffer = buffer;
  req->len = len;
  req->src = src;
  req->dest = dest;
  req->tag = tag;

  return req;
}
