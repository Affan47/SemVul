qr_inverse(HepMatrix *A)
{
   if (A->num_row()!=A->num_col()) {
      HepGenMatrix::error("qr_inverse: The matrix is not square.");
   }
   HepMatrix QT=qr_decomp(A).T();
   back_solve(*A,&QT);
   return QT;
}
