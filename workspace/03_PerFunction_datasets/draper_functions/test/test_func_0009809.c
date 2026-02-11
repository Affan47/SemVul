Finalize()
{


  vtkRenderer* ren;
  this->Renderers->InitTraversal();
  for ( ren = vtkOpenGLRenderer::SafeDownCast(this->Renderers->GetNextItemAsObject());
    ren != NULL;
    ren = vtkOpenGLRenderer::SafeDownCast(this->Renderers->GetNextItemAsObject())  )
    {
    ren->SetRenderWindow(NULL);
    ren->SetRenderWindow(this);
    }
}
