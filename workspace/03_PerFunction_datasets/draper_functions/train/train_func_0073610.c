ReadGraphDirectedness(bool & directed)
  {
  if(!this->OpenVTKFile() || !this->ReadHeader())
    {
    return 0;
    }


  char line[256];
  if(!this->ReadString(line))
    {
    vtkErrorMacro(<<"Data file ends prematurely!");
    this->CloseVTKFile();
    return 0;
    }

  if(strncmp(this->LowerCase(line),"dataset", (unsigned long)7))
    {
    vtkErrorMacro(<< "Unrecognized keyword: " << line);
    this->CloseVTKFile();
    return 0;
    }

  if(!this->ReadString(line))
    {
    vtkErrorMacro(<<"Data file ends prematurely!");
    this->CloseVTKFile ();
    return 0;
    }

  if(!strncmp(this->LowerCase(line),"directed_graph", 14))
    {
    directed = true;
    }
  else if(!strncmp(this->LowerCase(line), "undirected_graph", 16))
    {
    directed = false;
    }
  else
    {
    vtkErrorMacro(<< "Cannot read type: " << line);
    this->CloseVTKFile();
    return 0;
    }
  return 1;
}
