getImageFileName(GooString *outputFileName, int numDigits, int page)
{
  char buf[10];
  GooString *imageName = new GooString(outputFileName);
  if (!singleFile) {
    snprintf(buf, sizeof(buf), "-%0*d", numDigits, page);
    imageName->appendf(buf);
  }
  if (png)
    imageName->append(".png");
  else if (jpeg)
    imageName->append(".jpg");

  return imageName;
}
