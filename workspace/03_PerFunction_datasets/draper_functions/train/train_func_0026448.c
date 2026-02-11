SupportsDimension(unsigned long dim)
{
  if ( 1 == this->GetNumberOfComponents() )
    {
    return dim <= NRRD_DIM_MAX;
    }
  else
    {
    return dim <= NRRD_DIM_MAX - 1;
    }
}
