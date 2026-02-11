CanReadFileVersion(int major, int vtkNotUsed(minor))
{
  if (major > 0)
    {
    return 0;
    }
  return 1;
}
