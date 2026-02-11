EvaluateDualCorner(
  vtkHyperOctreeLightWeightCursor* neighborhood)
{
  unsigned char numCorners = 1 << this->GetDimension();
  unsigned char corner;

  vtkIdType leaves[8];

  for (corner = 0; corner < numCorners; ++corner)
    {


    if (!neighborhood[corner].GetTree())
      {
      return;
      }
    leaves[corner] = neighborhood[corner].GetLeafIndex();
    }

  this->CornerLeafIds->InsertNextTupleValue(leaves);
}
