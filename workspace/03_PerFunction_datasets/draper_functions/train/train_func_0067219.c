ReadLineThickness(vtkProperty *property)
{
  vtkFloatArray *tmpArray = vtkFloatArray::New();

  int status = this->ParseValues(tmpArray, 1);

  if (status != 0)
    {
    property->SetLineWidth(tmpArray->GetValue(0));
    }

  tmpArray->Delete();

  return status;
}
