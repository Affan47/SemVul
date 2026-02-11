operator+(const HepMatrix &m1,const HepMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.nrow, m1.ncol);
{
#else
{
  HepMatrix mret(m1.nrow, m1.ncol);
#endif
  CHK_DIM_2(m1.num_row(),m2.num_row(), m1.num_col(),m2.num_col(),+);
  SIMPLE_TOP(+)
  return mret;
}
