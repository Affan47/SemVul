SetExtent(int extent[6])
{
  int description;

  description = vtkStructuredData::SetExtent(extent, this->Extent);

  if ( description < 0 )
    {
    vtkErrorMacro (<< "Bad Extent, retaining previous values");
    }

  if (description == VTK_UNCHANGED)
    {
    return;
    }

  this->DataDescription = description;

  this->Modified();
  this->Dimensions[0] = extent[1] - extent[0] + 1;
  this->Dimensions[1] = extent[3] - extent[2] + 1;
  this->Dimensions[2] = extent[5] - extent[4] + 1;
}
