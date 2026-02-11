GetNthFileName(int index)
{
  if(index >= this->FileNames->GetNumberOfValues() || index < 0)
    {
    vtkErrorMacro( << "Bad index for GetFileName on vtkGlobFileNames\n");
    return 0;
    }

  return this->FileNames->GetValue(index).c_str();
}
