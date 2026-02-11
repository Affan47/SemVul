RenderTranslucentPolygonalGeometry(vtkViewport *ren)
{
  vtkProp *prop;
  vtkAssemblyPath *path;
  double fraction;
  int renderedSomething=0;


  this->UpdatePaths();

  double numberOfItems =  static_cast<double>(this->Parts->GetNumberOfItems());
  fraction = numberOfItems >= 1.0 ?
    this->AllocatedRenderTime / numberOfItems : this->AllocatedRenderTime;


  vtkCollectionSimpleIterator sit;
  for ( this->Paths->InitTraversal(sit); (path = this->Paths->GetNextPath(sit)); )
    {
    prop = path->GetLastNode()->GetViewProp();
    if ( prop->GetVisibility() )
      {
      prop->SetAllocatedRenderTime(fraction, ren);
      prop->PokeMatrix(path->GetLastNode()->GetMatrix());
      renderedSomething += prop->RenderTranslucentPolygonalGeometry(ren);
      prop->PokeMatrix(NULL);
      }
    }

  return renderedSomething;
}
