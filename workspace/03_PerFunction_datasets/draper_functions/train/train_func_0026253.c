RemoveAllViewProps(void)
{
  vtkProp *aProp;
  vtkCollectionSimpleIterator pit;
  for (this->Props->InitTraversal(pit);
       (aProp = this->Props->GetNextProp(pit)); )
    {
    aProp->ReleaseGraphicsResources(this->VTKWindow);
    aProp->RemoveConsumer(this);
    }
  this->Props->RemoveAllItems();
}
