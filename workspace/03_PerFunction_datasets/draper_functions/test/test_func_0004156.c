vt_request_free(struct VTRequest* req)
{
#if defined(HAVE_MPI_TYPE_DUP) && HAVE_MPI_TYPE_DUP

  PMPI_Type_free(&(req->datatype));
#endif


  if (!lastreq) {
    vt_error_msg("INTERNAL ERROR in request handling - no last request");
  }
  *req = *lastreq;
  lastreq->flags = ERF_NONE;
  lastreq->request = 0;


  lastidx--;
  if (lastidx < 0)
    {

      if (last_block->prev)
	{

	  lastidx = VT_REQBLK_SIZE-1;
	  lastreq = &(last_block->prev->req[lastidx]);
	}
      else
	{

	  lastidx = VT_REQBLK_SIZE;
	  lastreq = 0;
	}
      last_block = last_block->prev;
    }
  else
    {
      lastreq--;
    }
}
