operator+(const HepDiagMatrix &m1,const HepSymMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m2);
{
#else
{
  HepSymMatrix mret(m2);
#endif
  CHK_DIM_1(m1.num_row(),m2.num_row(),+);
  mret += m1;
  return mret;
}
