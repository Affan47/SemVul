Write(const char *filename) const
{

  const char *input_extension;
  if (!(input_extension = strrchr(filename, '.'))) {
    fprintf(stderr, "Input file has no extension (e.g., .jpg).\n");
    return 0;
  }


  if (!strncmp(input_extension, ".bmp", 4)) return WriteBMP(filename);
  else if (!strncmp(input_extension, ".ppm", 4)) return WritePPM(filename, 1);
  else if (!strncmp(input_extension, ".jpg", 4)) return WriteJPEG(filename);
  else if (!strncmp(input_extension, ".jpeg", 5)) return WriteJPEG(filename);
  else if (!strncmp(input_extension, ".tif", 4)) return WriteTIFF(filename);
  else if (!strncmp(input_extension, ".tiff", 5)) return WriteTIFF(filename);
  else if (!strncmp(input_extension, ".raw", 4)) return WriteRAW(filename);


  fprintf(stderr, "Unrecognized image file extension");
  return 0;
}
