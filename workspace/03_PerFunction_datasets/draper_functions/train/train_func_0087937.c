SortFileNames(vtkStringArray *input,
                                     vtkStringArray *output)
{

  std::vector<std::string> fileNames;
  unsigned int numberOfStrings = input->GetNumberOfValues();
  for (unsigned int j = 0; j < numberOfStrings; j++)
    {
    std::string& fileName = input->GetValue(j);


    if (this->SkipDirectories &&
        vtksys::SystemTools::FileIsDirectory(fileName.c_str()))
      {
      continue;
      }


    fileNames.push_back(fileName);
    }


  if (this->IgnoreCase)
    {
    if (this->NumericSort)
      {

      std::sort(fileNames.begin(), fileNames.end(),
                   vtkCompareFileNamesNumericIgnoreCase);
      }
    else
      {

      std::sort(fileNames.begin(), fileNames.end(),
                   vtkCompareFileNamesIgnoreCase);
      }
    }
  else
    {
    if (this->NumericSort)
      {

      std::sort(fileNames.begin(), fileNames.end(),
                   vtkCompareFileNamesNumeric);
      }
    else
      {

      std::sort(fileNames.begin(), fileNames.end());
      }
    }


  std::vector<std::string>::iterator iter = fileNames.begin();
  while (iter < fileNames.end())
    {
    output->InsertNextValue(*iter++);
    }
}
