testForEncapsulatedXferSyntax(const char* fileXferSyntax)
{
  char* xfer[] = {
    DICOM_TRANSFERLITTLEENDIAN,
    DICOM_TRANSFERLITTLEENDIANEXPLICIT,
    DICOM_TRANSFERBIGENDIANEXPLICIT
  };
  int index;

  if (fileXferSyntax == 0)
    return 0;

  for (index = 0; index < 3; index++) {
    if (strcmp(xfer[index], fileXferSyntax) == 0)
      return 0;
  }

  return 1;
}
