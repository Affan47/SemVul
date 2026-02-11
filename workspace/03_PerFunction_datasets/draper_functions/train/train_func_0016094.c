lam_mkcoll(MPI_Comm comm)
{
  if (comm)
    comm->c_contextid = lam_pt2coll(comm->c_contextid);
}
