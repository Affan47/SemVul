CreateAllInstance(const char* vtkclassname,
                                               vtkCollection* retList)
{
  vtkObjectFactory* f;
  vtkObjectFactoryCollection* collection
    = vtkObjectFactory::GetRegisteredFactories();
  vtkCollectionSimpleIterator osit;
  for(collection->InitTraversal(osit);
      (f = collection->GetNextObjectFactory(osit)); )
    {
    vtkObject* o = f->CreateObject(vtkclassname);
    if(o)
      {
      retList->AddItem(o);
      o->Delete();
      }
    }
}
