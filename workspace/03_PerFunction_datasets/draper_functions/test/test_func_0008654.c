GetScalarsForExtent(
  vtkDataArray *array, int extent[6], vtkRectilinearGrid *input)
{
  if ( ! array )
    {
    return NULL;
    }

  int increments[3], iExt[6], idx;

  input->GetExtent(iExt);

  for (idx = 0; idx < 3; idx++)
    {
    if (extent[idx*2] < iExt[idx*2] ||
        extent[idx*2] > iExt[idx*2+1])
      {
      vtkErrorMacro("requested extent not in input's extent");
      return NULL;
      }
    }

  increments[0] = array->GetNumberOfComponents();
  increments[1] = increments[0] * (iExt[1]-iExt[0]+1);
  increments[2] = increments[1] * (iExt[3]-iExt[2]+1);

  idx = (extent[0] - iExt[0]) * increments[0] +
    (extent[2] - iExt[2]) * increments[1] +
    (extent[4] - iExt[4]) * increments[2];

  if (idx < 0 || idx > array->GetMaxId())
    {
    vtkErrorMacro("computed coordinate outside of array bounds");
    return NULL;
    }

  return array->GetVoidPointer(idx);
}
