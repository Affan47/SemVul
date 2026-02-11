ddf_CreateMatrix(ddf_rowrange m_size,ddf_colrange d_size)
{
  ddf_MatrixPtr M;
  ddf_rowrange m0,m1;
  ddf_colrange d0,d1;

  if (m_size<=0){
    m0=0; m1=1;

  } else {
    m0=m_size; m1=m_size;
  }
  if (d_size<=0){
    d0=0; d1=1;

  } else {
    d0=d_size; d1=d_size;
  }
  M=(ddf_MatrixPtr) malloc (sizeof(ddf_MatrixType));
  ddf_InitializeAmatrix(m1,d1,&(M->matrix));
  ddf_InitializeArow(d1,&(M->rowvec));
  M->rowsize=m0;
  set_initialize(&(M->linset), m1);
  M->colsize=d0;
  M->objective=ddf_LPnone;
  M->numbtype=ddf_Unknown;
  M->representation=ddf_Unspecified;
  return M;
}
