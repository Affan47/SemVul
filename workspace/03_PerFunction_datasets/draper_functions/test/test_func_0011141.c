imFileImageLoadBitmap(const char* file_name, int index, int *error)
{
  imFile* ifile = imFileOpen(file_name, error);
  if (!ifile) return NULL;
  imImage* image = imFileLoadBitmap(ifile, index, error);
  imFileClose(ifile);
  return image;
}
