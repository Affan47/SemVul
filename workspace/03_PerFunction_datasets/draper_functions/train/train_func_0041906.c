CblacsGetRowComm(int ctxt) {
  CBLACS_CHK_CTXT(MPI_COMM_NULL);
  return CblacsComms[ctxt - 1].rowComm;
}
