vtkSortDataArrayComponentCompare_VTK_VARIANT( const void* a, const void* b )
{
  vtkVariantLessThan comp;
  return comp(((vtkVariant*)a)[vtkSortDataArrayComp], ((vtkVariant*)b)[vtkSortDataArrayComp]) ? -1 :
    (comp(((vtkVariant*)b)[vtkSortDataArrayComp], ((vtkVariant*)a)[vtkSortDataArrayComp]) ? 1 : 0);
}
