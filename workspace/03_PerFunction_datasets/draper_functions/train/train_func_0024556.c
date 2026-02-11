NormalizedDisplayToDisplay(double &u, double &v)
{
  if ( this->VTKWindow )
    {
    int *size = NULL;


    size = this->VTKWindow->GetSize();
    if (size)
      {
      u = u*size[0];
      v = v*size[1];
      }
    }
}
