Create_intercomm(int local_leader,
						const MPI::Comm& peer_comm,
						int remote_leader, int tag) const
{
  return pmpi_comm.Create_intercomm(local_leader, peer_comm, remote_leader, tag);
}
