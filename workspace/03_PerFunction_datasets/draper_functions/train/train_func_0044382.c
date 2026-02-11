BuildWarpVectors(vtkUnstructuredGrid* input)
{
  double warpVector[3];
  double layerThickness;

  vtkIdType numberOfInputPoints = input->GetNumberOfPoints();

  for (vtkIdType i=0; i<numberOfInputPoints; i++)
    {
    this->WarpVectorsArray->GetTuple(i,warpVector);
    if (this->NegateWarpVectors)
      {
      warpVector[0] *= -1.0;
      warpVector[1] *= -1.0;
      warpVector[2] *= -1.0;
      }
    layerThickness = 0.0;
    if (this->ConstantThickness)
      {
      layerThickness = this->LayerThickness;
      }
    else if (this->UseWarpVectorMagnitudeAsThickness)
      {
      layerThickness = vtkMath::Norm(warpVector);
      }
    else
      {
      layerThickness = this->LayerThicknessArray->GetComponent(i,0);
      layerThickness *= this->LayerThicknessRatio;
      }
    if (layerThickness > this->MaximumLayerThickness)
      {
      layerThickness = this->MaximumLayerThickness;
      }
    vtkMath::Normalize(warpVector);
    warpVector[0] = warpVector[0] * layerThickness;
    warpVector[1] = warpVector[1] * layerThickness;
    warpVector[2] = warpVector[2] * layerThickness;

    this->WarpVectorsArray->SetTuple(i,warpVector);
    }
}
