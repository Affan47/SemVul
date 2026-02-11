max(const std::vector< std::vector<int> >& matrix) {
  int m = matrix.at(0).at(0);
  for (unsigned i = 0; i < matrix.size(); ++i)
    for (unsigned j = 0; j < matrix[i].size(); ++j)
      m = std::max(m, matrix[i][j]);
  return m;
}
