remote_group() const
{
  MPI_Group gr;
  BOOST_MPI_CHECK_RESULT(MPI_Comm_remote_group, ((MPI_Comm)*this, &gr));
  return boost::mpi::group(gr, true);
}
