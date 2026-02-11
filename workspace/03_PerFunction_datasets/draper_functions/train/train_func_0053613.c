RenderVolumetricGeometry(vtkViewport *ren)
{
  vtkProp3D *prop3D;
  vtkAssemblyPath *path;
  double fraction;
  int renderedSomething = 0;

  this->UpdatePaths();


  fraction = this->AllocatedRenderTime
    / static_cast<double>(this->Paths->GetNumberOfItems());


  vtkCollectionSimpleIterator sit;
  for ( this->Paths->InitTraversal(sit); (path = this->Paths->GetNextPath(sit)); )
    {
    prop3D = static_cast<vtkProp3D *>(path->GetLastNode()->GetViewProp());
    if ( prop3D->GetVisibility() )
      {
      prop3D->SetAllocatedRenderTime(fraction, ren);
      prop3D->PokeMatrix(path->GetLastNode()->GetMatrix());
      renderedSomething += prop3D->RenderVolumetricGeometry(ren);
      prop3D->PokeMatrix(NULL);
      }
    }

  renderedSomething = (renderedSomething > 0)?(1):(0);

  return renderedSomething;
}
