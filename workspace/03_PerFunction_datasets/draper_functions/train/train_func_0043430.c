mca_vprotocol_pessimist_probe( int src, int tag,
                       struct ompi_communicator_t *comm,
                       ompi_status_public_t * status )
{
  int ret;

  if(mca_vprotocol_pessimist.replay)
  {
    ret = replay_probe(src, tag, comm, status);
  }
  else
  {
    ret = mca_pml_v.host_pml.pml_probe(src, tag, comm, status);
    log_probe(ret, src, tag, comm, status);
  }
  return ret;
}
