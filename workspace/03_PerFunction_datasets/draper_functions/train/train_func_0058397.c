Initialize(vtkDataObject *o)
{

  this->ReleaseData();


  vtkImageData *data = vtkImageData::SafeDownCast(o);
  vtkDataArray *scalars = NULL;
  if (data)
    {
    scalars = data->GetPointData()->GetScalars();
    }

  if (data == NULL || scalars == NULL)
    {
    vtkErrorMacro("Initialize(): no image data to interpolate!");
    return;
    }


  scalars->Register(this);
  this->Scalars = scalars;


  data->GetSpacing(this->Spacing);
  data->GetOrigin(this->Origin);
  data->GetWholeExtent(this->WholeExtent);
  data->GetExtent(this->Extent);


  this->Update();
}
