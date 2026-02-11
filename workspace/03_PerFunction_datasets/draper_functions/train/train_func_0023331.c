NewClone(vtkDataObject* data)
{
  if (data->IsA("vtkDataSet"))
    {
    vtkDataSet* ds = vtkDataSet::SafeDownCast(data);
    vtkDataSet* clone = ds->NewInstance();
    clone->ShallowCopy(ds);


    clone->GetCellData()->SetScalars(0);
    clone->GetPointData()->SetScalars(0);


    clone->GetFieldData()->Initialize();
    return clone;
    }
  else if (data->IsA("vtkCompositeDataSet"))
    {
    vtkCompositeDataSet* cd = vtkCompositeDataSet::SafeDownCast(data);
    vtkCompositeDataSet* clone = cd->NewInstance();
    clone->CopyStructure(cd);
    vtkCompositeDataIterator* iter = cd->NewIterator();
    for (iter->InitTraversal();
      !iter->IsDoneWithTraversal(); iter->GoToNextItem())
      {
      vtkDataObject* leafClone = this->NewClone(iter->GetCurrentDataObject());
      clone->SetDataSet(iter, leafClone);
      leafClone->Delete();
      }
    iter->Delete();
    return clone;
    }
  return 0;
}
