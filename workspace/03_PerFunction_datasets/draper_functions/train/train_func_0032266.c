ReadDataset(
  vtkXMLDataElement* xmlElem, const char* filePath)
{
  vtkDataSet* ds = this->Superclass::ReadDataset(xmlElem, filePath);
  if (ds && ds->IsA("vtkImageData"))
    {


    vtkUniformGrid* ug = vtkUniformGrid::New();
    ug->ShallowCopy(ds);
    ds->Delete();
    return ug;
    }
  return ds;
}
