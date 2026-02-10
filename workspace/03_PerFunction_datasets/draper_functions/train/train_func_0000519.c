size() const
{
  if (!group_ptr)
    return 0;

  int size;
  BOOST_MPI_CHECK_RESULT(MPI_Group_size, (*group_ptr, &size));
  return size;
}
