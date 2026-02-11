GetAsEdgeMatrix(std::vector<std::vector<bool> >& edges) const
{
  edges.resize(data.size()+1,std::vector<bool>(data.size()+1, false));
  for (size_t i=0; i<data.size(); ++i) {
    for (size_t j=0; j<data[i].size(); ++j) {
      edges[i][i+next_nodes[i][j]] = true;
    }
  }
}
