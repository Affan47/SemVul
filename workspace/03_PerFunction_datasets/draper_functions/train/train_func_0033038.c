SetComponentExtent(int extent[6])
{
  int idx, modified = 0;

  for (idx = 0; idx < 6; ++idx)
    {
    if (this->ComponentExtent[idx] != extent[idx])
      {
      this->ComponentExtent[idx] = extent[idx];
      modified = 1;
      }
    }
  if (modified)
    {
    this->Modified();
    }
}
