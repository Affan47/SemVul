GetActors(vtkPropCollection *ac)
{
  vtkProp3D *prop3D;
  vtkActor *actor;
  vtkAssemblyPath *path;

  this->UpdatePaths();
  vtkCollectionSimpleIterator sit;
  for ( this->Paths->InitTraversal(sit); (path = this->Paths->GetNextPath(sit)); )
    {
    prop3D = static_cast<vtkProp3D *>(path->GetLastNode()->GetViewProp());
    if ( (actor = vtkActor::SafeDownCast(prop3D)) != NULL )
      {
      ac->AddItem(actor);
      }
    }
}
