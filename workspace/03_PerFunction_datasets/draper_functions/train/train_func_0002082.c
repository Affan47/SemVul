apply(double (*f)(double, int, int)) const
#ifdef HEP_GNU_OPTIMIZED_RETURN
return mret(num_row());
{
#else
{
  HepDiagMatrix mret(num_row());
#endif
  HepMatrix::mcIter a = m.begin();
  HepMatrix::mIter b = mret.m.begin();
  for(int ir=1;ir<=num_row();ir++) {
    *(b++) = (*f)(*(a++), ir, ir);
  }
  return mret;
}
