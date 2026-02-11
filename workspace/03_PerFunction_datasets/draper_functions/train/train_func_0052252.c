EvaluateFunction(double x[3])
{
  double sum = 0;
  double c;
  int i;
  vtkImplicitFunction *f;
  double *weights = this->Weights->GetPointer(0);

  vtkCollectionSimpleIterator sit;
  for (i = 0, this->FunctionList->InitTraversal(sit);
       (f=this->FunctionList->GetNextImplicitFunction(sit)); i++)
    {
    c = weights[i];
    if (c != 0.0)
      {
      sum += f->FunctionValue(x)*c;
      }
    }
  if (this->NormalizeByWeight && this->TotalWeight != 0.0)
    {
    sum /= this->TotalWeight;
    }
  return sum;
}
