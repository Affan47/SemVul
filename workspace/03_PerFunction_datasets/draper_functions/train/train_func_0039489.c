newImageAndAlloc(int xlen, int ylen)
{
  const char  modName[] = "newImageAndAlloc";
  VimosImage *tmpImage;

  tmpImage = newImage(xlen, ylen, NULL);
  if (tmpImage == NULL) {
    cpl_msg_error(modName, "Allocation Error");
    return(NULL);
  }

  tmpImage->data = (float *)pil_calloc(xlen * ylen, sizeof(float));
  if (tmpImage->data == NULL) {

    deleteImage(tmpImage);
    cpl_msg_error(modName, "Allocation Error");
    return(NULL);
  }

  return(tmpImage);

}
