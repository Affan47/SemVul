determinantSign(IntegerVectorList const &l)
{


  FieldMatrix M=integerMatrixToFieldMatrix(rowsToIntegerMatrix(l),Q);
  FieldElement d=M.reduceAndComputeDeterminant();
  int swaps=0;

  string s=d.toString(true,true);
  if(d.isZero())return 0;
  if(s[0]=='+')
    {
      if(swaps&1)return -1;
      else return 1;
    }
  if(s[0]=='-')
    {
      if(swaps&1)return 1;
      else return -1;
    }
  return 0;
}
