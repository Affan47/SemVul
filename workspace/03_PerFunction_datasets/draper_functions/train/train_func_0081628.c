kernelvercmp(int major1, int minor1, int patch1,
    int major2, int minor2, int patch2)
{
  if (major1 != major2)
    return major1 - major2;
  if (minor1 != minor2)
    return minor1 - minor2;
  return patch1 - patch2;
}
