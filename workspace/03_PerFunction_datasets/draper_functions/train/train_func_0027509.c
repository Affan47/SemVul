Write(const char *filename) const
{

  const char *input_extension;
  if (!(input_extension = strrchr(filename, '.'))) {
    fprintf(stderr, "Input file has no extension (e.g., .pfm).\n");
    return 0;
  }


  if (!strncmp(input_extension, ".raw", 4)) return WriteRAW(filename);
  else if (!strncmp(input_extension, ".pfm", 4)) return WritePFM(filename);
  else if (!strncmp(input_extension, ".grd", 4)) return WriteGRD(filename);
  else return WriteImage(filename);


  fprintf(stderr, "Unrecognized image file extension");
  return 0;
}
