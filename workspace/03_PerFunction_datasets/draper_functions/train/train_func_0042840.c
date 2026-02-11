SparseMatrix_export(FILE *f, SparseMatrix A){

  switch (A->format){
  case FORMAT_CSR:
    SparseMatrix_export_csr(f, A);
    break;
  case FORMAT_CSC:
    assert(0);

    break;
  case FORMAT_COORD:
    SparseMatrix_export_coord(f, A);
    break;
  default:
    assert(0);
  }
}
