EndElement(const char* tname)
  {
    const char* name=strrchr(tname,':');
    if (!name)
      {
      name=tname;
      }
    else
      {
      name++;
      }

    if (strcmp(name,"assembly")==0)
      {
      this->CurrentAssemblyNumbers.pop_back();
      this->CurrentAssemblyDescriptions.pop_back();
      }
    else if (strcmp(name,"blocks")==0)
      {
      this->PartNumber="";
      }
    else if (strcmp(name,"material-assignments")==0)
      {
      this->ParseMaterials=0;
      }
  }
