operator+(const HepMatrix &m1,const HepSymMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepMatrix mret(m1);
#endif
  CHK_DIM_2(m1.num_row(),m2.num_row(), m1.num_col(),m2.num_col(),+);
  mret += m2;
  return mret;
}
