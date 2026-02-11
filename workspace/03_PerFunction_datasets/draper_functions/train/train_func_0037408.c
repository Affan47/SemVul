RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *vtkNotUsed(outputVector))
{
  int first, last;
  int *dim;
  int dimensions[3];
  double Spacing[3];
  double origin[3];

  vtkImageData *output = this->AllocateOutputData(this->GetOutput());
  vtkUnsignedShortArray *newScalars =
    vtkUnsignedShortArray::SafeDownCast(output->GetPointData()->GetScalars());


  if (this->FilePrefix == NULL)
    {
    vtkErrorMacro(<< "FilePrefix is NULL");
    return 1;
    }

  if (this->HeaderSize < 0)
    {
    vtkErrorMacro(<< "HeaderSize " << this->HeaderSize << " must be >= 0");
    return 1;
    }

  dim = this->DataDimensions;

  if (dim[0] <= 0 || dim[1] <= 0)
    {
    vtkErrorMacro(<< "x, y dimensions " << dim[0] << ", " << dim[1]
                  << "must be greater than 0.");
    return 1;
    }

  if ( (this->ImageRange[1]-this->ImageRange[0]) <= 0 )
    {
    this->ReadImage(this->ImageRange[0], newScalars);
    }
  else
    {
    first = this->ImageRange[0];
    last = this->ImageRange[1];
    this->ReadVolume(first, last, newScalars);
    }


  this->ComputeTransformedDimensions (dimensions);
  output->SetDimensions(dimensions);


  this->ComputeTransformedSpacing(Spacing);


  this->ComputeTransformedOrigin(origin);


  this->AdjustSpacingAndOrigin(dimensions, Spacing, origin);

  output->SetSpacing(Spacing);
  output->SetOrigin(origin);

  return 1;
}
