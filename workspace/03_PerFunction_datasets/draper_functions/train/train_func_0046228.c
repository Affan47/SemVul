GetVRMLDEFObject(const char *name)
{


  for (int i = VrmlNodeType::useList->Count()-1;i >=0 ; i--)
    {
    const vtkVRMLUseStruct *nt = (*VrmlNodeType::useList)[i];
    if (nt != NULL && strcmp(nt->defName,name) == 0)
      {
      return nt->defObject;
      }
    }
  return NULL;
}
