horconcat2myright(const SparseMatrix& B)
 {
   Tracer_Plus tr("SparseMatrix::horconcat2myright");

   if (Nrows() != B.Nrows()) {throw Exception("Rows don't match in SparseMatrix::vertconcat2myright");}

   for (int i=1; i<=Nrows(); i++) {
     const SparseMatrix::Row& tmpRow = B.row(i);
     for (SparseMatrix::Row::const_iterator it=tmpRow.begin(); it!=tmpRow.end(); it++) {
       this->insert(i,Ncols()+int(it->first)+1,double(it->second));
     }
   }
   ncols += B.Ncols();
 }
