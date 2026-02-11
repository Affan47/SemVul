SetFileName(const char* name)
{
  VTK_LEGACY_BODY(vtkExodusReader, "VTK 5.8");
  vtkDebugMacro(<< this->GetClassName() << " (" << this << "): setting FileName to " << (name?name:"(null)") );
  if ( this->FileName == NULL && name == NULL) { return;}
  if ( this->FileName && name && (!strcmp(this->FileName,name))) { return;}
  if (this->FileName) { delete [] this->FileName; }
  if (name)
    {
    size_t n = strlen(name) + 1;
    this->FileName =  new char[n];
    strncpy(this->FileName,name,n);
    }
   else
    {
    this->FileName = NULL;
    }
  this->Modified();
}
