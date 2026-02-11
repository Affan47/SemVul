ComputeTransformedBounds (int bounds[6])
{
  double transformedBounds[4];

  if (!this->Transform)
    {
    bounds[0] = 0;
    bounds[1] = this->DataDimensions[0] - 1;
    bounds[2] = 0;
    bounds[3] = this->DataDimensions[1] - 1;
    bounds[4] = 0;
    bounds[5] = this->ImageRange[1] - this->ImageRange[0];
    }
  else
    {
    transformedBounds[0] = 0;
    transformedBounds[1] = 0;
    transformedBounds[2] = 0;
    transformedBounds[3] = 1.0;
    this->Transform->MultiplyPoint (transformedBounds, transformedBounds);
    bounds[0] = (int) transformedBounds[0];
    bounds[2] = (int) transformedBounds[1];
    bounds[4] = (int) transformedBounds[2];
    transformedBounds[0] = this->DataDimensions[0] - 1;
    transformedBounds[1] = this->DataDimensions[1] - 1;
    transformedBounds[2] = this->ImageRange[1] - this->ImageRange[0];
    transformedBounds[3] = 1.0;
    this->Transform->MultiplyPoint (transformedBounds, transformedBounds);
    bounds[1] = (int) transformedBounds[0];
    bounds[3] = (int) transformedBounds[1];
    bounds[5] = (int) transformedBounds[2];

    int tmp;
    for (int i = 0; i < 6; i += 2)
      {
      if (bounds[i + 1] < bounds[i])
        {
        tmp = bounds[i];
        bounds[i] = bounds[i + 1];
        bounds[i + 1] = tmp;
        }
      }
    vtkDebugMacro(<< "Transformed bounds are: "
                << bounds[0] << ", " << bounds[1] << ", "
                << bounds[2] << ", " << bounds[3] << ", "
                << bounds[4] << ", " << bounds[5]);
    }
}
