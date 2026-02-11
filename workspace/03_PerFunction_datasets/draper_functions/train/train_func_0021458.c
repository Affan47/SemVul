DisplayToNormalizedDisplay(double &u, double &v)
{
  if ( this->VTKWindow )
    {
    int *size = NULL;


    size = this->VTKWindow->GetSize();

    if (size &&
        size[0] != 0 &&
        size[1] != 0)
      {
      u = u/size[0];
      v = v/size[1];
      }
    }
}
