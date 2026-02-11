assignProblem(CoinPackedMatrix*& matrix,
					  double*& collb, double*& colub,
					  double*& obj, double*& rowlb,
					  double*& rowub)

{
   loadProblem( *matrix, collb, colub, obj, rowlb, rowub );
   delete matrix;   matrix = 0;
   delete[] collb;  collb = 0;
   delete[] colub;  colub = 0;
   delete[] obj;    obj = 0;
   delete[] rowlb;  rowlb = 0;
   delete[] rowub;  rowub = 0;
}
