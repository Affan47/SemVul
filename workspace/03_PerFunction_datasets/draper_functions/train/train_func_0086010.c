assign(const HepSymMatrix &m1)
{
   if(m1.num_row()!=nrow)
   {
      nrow = m1.num_row();
      m.resize(nrow);
   }
   HepMatrix::mcIter a = m1.m.begin();
   HepMatrix::mIter b = m.begin();
   for(int r=1;r<=nrow;r++) {
      *(b++) = *a;
      if(r<nrow) a += (r+1);
   }
}
