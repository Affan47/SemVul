broadcast<packed_iarchive>(const communicator& comm, packed_iarchive& ia,
                           int root)
{
  int size = comm.size();
  if (size < 2) return;


  int tag = environment::collectives_tag();


  if (comm.rank() != root) {
    MPI_Status status;
    detail::packed_archive_recv(comm, root, tag, ia, status);
  } else {

    std::vector<MPI_Request> requests(size * 2);
    int num_requests = 0;
    for (int dest = 0; dest < size; ++dest) {
      if (dest != root) {

        num_requests += detail::packed_archive_isend(comm, dest, tag, ia,
                                                     &requests[num_requests],
                                                     2);
      }
    }


    BOOST_MPI_CHECK_RESULT(MPI_Waitall,
                           (num_requests, &requests[0], MPI_STATUSES_IGNORE));
  }
}
