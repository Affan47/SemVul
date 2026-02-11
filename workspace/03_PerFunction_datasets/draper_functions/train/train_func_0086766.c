getFileNameForPlatform()
{
  if (platformFileName)
    return platformFileName;

  Object obj1;
  if (getFileSpecNameForPlatform(&fileSpec, &obj1))
    platformFileName = obj1.getString()->copy();
  obj1.free();

  return platformFileName;
}
