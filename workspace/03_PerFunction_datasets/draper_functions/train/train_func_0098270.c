send_to_self_match(MPI_Request send, MPI_Request recv)
{
  int len;

  recv->rq_seq = send->rq_seq;
  if (recv->rq_type == LAM_RQIPROBE) {


    lam_ssi_rpi_fill_mpi_status(recv, send->rq_rpi->cq_env.ce_rank,
			 send->rq_rpi->cq_env.ce_tag,
			 send->rq_rpi->cq_env.ce_len);

    recv->rq_state = LAM_RQSDONE;
    lam_rq_nactv--;
    return (0);
  } else {


    if (send->rq_packsize > recv->rq_packsize) {
      recv->rq_flags |= LAM_RQFTRUNC;
      len = recv->rq_packsize;
    } else
      len = send->rq_packsize;

    lam_memcpy(recv->rq_packbuf, send->rq_packbuf, len);

    lam_ssi_rpi_fill_mpi_status(recv, send->rq_rpi->cq_env.ce_rank,
				send->rq_rpi->cq_env.ce_tag, len);

    send->rq_state = recv->rq_state = LAM_RQSDONE;
    lam_rq_nactv--;
    return (1);
  }
}
