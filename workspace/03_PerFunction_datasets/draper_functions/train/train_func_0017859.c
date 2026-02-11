RenderTranslucentPolygonalGeometry(vtkViewport *v)
{
  int count=0;
  this->BuildRepresentation();
  count += this->LineActor->RenderTranslucentPolygonalGeometry(v);
  count += this->Handle[0]->RenderTranslucentPolygonalGeometry(v);
  count += this->Handle[1]->RenderTranslucentPolygonalGeometry(v);
  if (this->DistanceAnnotationVisibility)
    {
    count += this->TextActor->RenderTranslucentPolygonalGeometry(v);
    }

  return count;
}
