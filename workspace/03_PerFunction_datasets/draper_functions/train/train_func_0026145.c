operator=(const HepVector &m1)
{
   if(m1.nrow != size_)
   {
      size_ = m1.nrow;
      m.resize(size_);
   }
   nrow = m1.nrow;
   ncol = 1;
   m = m1.m;
   return (*this);
}
