GetArrayPointer(vtkDataArray* array, int coordinate[3])
{
  vtkIdType incs[3];
  vtkIdType idx;

  if (array == NULL)
    {
    return NULL;
    }

  const int* extent = this->Extent;


  for (idx = 0; idx < 3; ++idx)
    {
    if (coordinate[idx] < extent[idx*2] ||
        coordinate[idx] > extent[idx*2+1])
      {
      vtkErrorMacro(<< "GetPointer: Pixel (" << coordinate[0] << ", "
        << coordinate[1] << ", "
        << coordinate[2] << ") not in current extent: ("
        << extent[0] << ", " << extent[1] << ", "
        << extent[2] << ", " << extent[3] << ", "
        << extent[4] << ", " << extent[5] << ")");
      return NULL;
      }
    }


  this->GetArrayIncrements(array, incs);
  idx = ((coordinate[0] - extent[0]) * incs[0]
         + (coordinate[1] - extent[2]) * incs[1]
         + (coordinate[2] - extent[4]) * incs[2]);


  if (idx < 0 || idx > array->GetMaxId())
    {
    vtkErrorMacro("Coordinate (" << coordinate[0] << ", " << coordinate[1]
                  << ", " << coordinate[2] << ") out side of array (max = "
                  << array->GetMaxId());
    return NULL;
    }

  return array->GetVoidPointer(idx);
}
