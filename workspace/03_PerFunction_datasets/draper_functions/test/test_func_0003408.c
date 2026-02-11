ReleaseGraphicsResources(vtkWindow *window)
{
  if(this->SourceMappers!=0)
    {
    size_t c=this->SourceMappers->Mappers.size();
    size_t i=0;
    while(i<c)
      {
      this->SourceMappers->Mappers[i]->ReleaseGraphicsResources(window);
      ++i;
      }
    }
  this->ReleaseList();
}
