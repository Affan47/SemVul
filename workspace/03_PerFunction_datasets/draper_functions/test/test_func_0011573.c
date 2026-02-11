CreateDataArray(int dataType)
{
  vtkAbstractArray* aa = vtkAbstractArray::CreateArray(dataType);
  vtkDataArray* da = vtkDataArray::SafeDownCast(aa);
  if (!da && aa)
    {

    aa->Delete();
    }
  return da;
}
