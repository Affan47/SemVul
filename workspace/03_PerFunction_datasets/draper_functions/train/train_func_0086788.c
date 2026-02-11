ClassFinalize()
{
  if(vtkCommonInformationKeyManagerKeys)
    {

    for(vtkCommonInformationKeyManagerKeysType::iterator i =
          vtkCommonInformationKeyManagerKeys->begin();
        i != vtkCommonInformationKeyManagerKeys->end(); ++i)
      {
      vtkInformationKey* key = *i;
      delete key;
      }


    vtkCommonInformationKeyManagerKeys->~vtkCommonInformationKeyManagerKeysType();
    free(vtkCommonInformationKeyManagerKeys);
    vtkCommonInformationKeyManagerKeys = 0;
    }
}
