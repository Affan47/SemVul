row_givens(HepMatrix *A, double c,double s,
		int k1, int k2, int col_min, int col_max) {

   if (col_max==0) col_max = A->num_col();
   int n = A->num_col();
   HepMatrix::mIter Ak1j = A->m.begin() + (k1-1) * n + (col_min-1);
   HepMatrix::mIter Ak2j = A->m.begin() + (k2-1) * n + (col_min-1);
   for (int j=col_min;j<=col_max;j++) {
      double tau1=(*Ak1j); double tau2=(*Ak2j);
      (*(Ak1j++))=c*tau1-s*tau2;(*(Ak2j++))=s*tau1+c*tau2;
   }
}
