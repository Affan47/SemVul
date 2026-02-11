InterpolatePoint(
  vtkDataSetAttributes::FieldList& list,
  vtkDataSetAttributes *fromPd,
  int idx,
  vtkIdType toId, vtkIdList *ptIds,
  double *weights)
{
  vtkAbstractArray *fromArray;
  vtkAbstractArray *toArray;

  for (int i=0; i < list.NumberOfFields; i++)
    {
    if ( list.FieldIndices[i] >= 0 && list.DSAIndices[idx][i] >= 0 )
      {
      toArray = this->GetAbstractArray(list.FieldIndices[i]);
      fromArray = fromPd->GetAbstractArray(list.DSAIndices[idx][i]);
      toArray->InterpolateTuple(toId, ptIds, fromArray, weights);
      }
    }
}
