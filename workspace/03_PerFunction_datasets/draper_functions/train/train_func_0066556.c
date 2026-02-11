CopyFieldOnOff(const char* field, int onOff)
{
  if (!field) { return; }

  int index;

  if ((index=this->FindFlag(field)) != -1)
    {
    if (this->CopyFieldFlags[index].IsCopied != onOff)
      {
      this->CopyFieldFlags[index].IsCopied = onOff;
      this->Modified();
      }
    }
  else
    {

    vtkFieldData::CopyFieldFlag* newFlags =
      new vtkFieldData::CopyFieldFlag[this->NumberOfFieldFlags+1];

    for(int i=0; i<this->NumberOfFieldFlags; i++)
      {
      newFlags[i].ArrayName = this->CopyFieldFlags[i].ArrayName;
      newFlags[i].IsCopied = this->CopyFieldFlags[i].IsCopied;
      }

    char* newName = new char[strlen(field)+1];
    strcpy(newName, field);
    newFlags[this->NumberOfFieldFlags].ArrayName = newName;
    newFlags[this->NumberOfFieldFlags].IsCopied = onOff;
    this->NumberOfFieldFlags++;
    delete[] this->CopyFieldFlags;
    this->CopyFieldFlags = newFlags;
    this->Modified();
    }
}
