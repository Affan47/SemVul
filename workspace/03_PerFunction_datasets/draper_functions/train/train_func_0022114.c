normalize(vector< vector<complex> >& matrix) {

  complex trace = 0;
  for (unsigned int i = 0; i < matrix.size(); i++) trace += matrix[i][i];
  for (unsigned int i = 0; i < matrix.size(); i++) {
    for (unsigned int j = 0; j < matrix.size(); j++) {
      if (trace != complex(0,0)) matrix[i][j] /= trace;
      else matrix[i][j] = 1 / static_cast<double>(matrix.size());
    }
  }

}
