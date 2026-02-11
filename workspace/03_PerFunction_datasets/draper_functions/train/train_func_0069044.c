GetFieldIndex(char* name)
{
  vtkStdString lcSearchName(name);
  std::transform(lcSearchName.begin(),
                    lcSearchName.end(),
                    lcSearchName.begin(),
                    (int(*)(int))tolower);

  int index;
  bool found = false;
  for (index = 0; index < this->GetNumberOfFields(); index++)
    {
    if (this->CaseSensitiveFieldNames)
      {
      if (!strcmp(name, this->GetFieldName(index)))
        {
        found = true;
        break;
        }
      }
    else
      {
      vtkStdString fieldName(this->GetFieldName(index));
      std::transform(fieldName.begin(),
                        fieldName.end(),
                        fieldName.begin(),
                        (int(*)(int))tolower);
      if (lcSearchName == fieldName)
        {
        found = true;
        break;
        }
      }
    }
  if (found)
    {
    return index;
    }
  return -1;
}
