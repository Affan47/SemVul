NormalizedViewportToViewport(double &u, double &v)
{
  if ( this->VTKWindow )
    {
    int *size = NULL;


    size = this->GetSize();
    if (size)
      {
      u = u * (size[0] - 1.0);
      v = v * (size[1] - 1.0);
      }
    }
}
