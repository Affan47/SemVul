adjacent_vertices(int vertex, const graph_communicator& comm)
{
  int nneighbors = out_degree(vertex, comm);
  shared_array<int> neighbors(new int[nneighbors]);
  BOOST_MPI_CHECK_RESULT(MPI_Graph_neighbors,
                         ((MPI_Comm)comm, vertex, nneighbors, neighbors.get()));
  return std::make_pair(detail::comm_adj_iterator(neighbors, 0),
                        detail::comm_adj_iterator(neighbors, nneighbors));
}
