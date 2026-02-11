translate_ranks(int* first, int* last, const group& to_group, int* out)
{
  BOOST_MPI_CHECK_RESULT(MPI_Group_translate_ranks,
                         ((MPI_Group)*this,
                          last-first,
                          first,
                          (MPI_Group)to_group,
                          out));
  return out + (last - first);
}
