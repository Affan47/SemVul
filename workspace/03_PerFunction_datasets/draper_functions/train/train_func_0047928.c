read_ascii_matrix(const string& filename, int nrows, int ncols)
  {
    Matrix mat(nrows,ncols);
    mat = 0.0;

    if ( filename.size()<1 ) return mat;
    ifstream fs(filename.c_str());
    if (!fs) {
      cerr << "Could not open matrix file " << filename << endl;
      return mat;
    }
    mat = read_ascii_matrix(fs,nrows,ncols);
    fs.close();
    mat.Release();
    return mat;
  }
