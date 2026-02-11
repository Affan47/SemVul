CopyArrayForPoints(vtkDataArray* inArray,
                                                     vtkDataArray* outArray)
{
  if(!inArray || !outArray)
    {
    return;
    }
  this->CopySubExtent(this->SubPieceExtent,
                      this->SubPiecePointDimensions,
                      this->SubPiecePointIncrements,
                      this->UpdateExtent, this->PointDimensions,
                      this->PointIncrements, this->SubExtent,
                      this->SubPointDimensions, inArray, outArray);
}
