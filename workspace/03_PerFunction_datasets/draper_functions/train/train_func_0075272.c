old_write_ascii_item(FILE *fp, char *item, int type)
{
  unsigned char *puchar;
  char *pchar;
  short int *pshort;
  unsigned short int *pushort;
  int *pint;
  unsigned int *puint;
  float *pfloat;
  double *pdouble;
  int int_value;
  unsigned int uint_value;
  double double_value;

  switch (type) {
    case PLY_CHAR:
      pchar = (char *) item;
      int_value = *pchar;
      fprintf (fp, "%d ", int_value);
      return ((double) int_value);
    case PLY_UCHAR:
      puchar = (unsigned char *) item;
      int_value = *puchar;
      fprintf (fp, "%d ", int_value);
      return ((double) int_value);
    case PLY_SHORT:
      pshort = (short int *) item;
      int_value = *pshort;
      fprintf (fp, "%d ", int_value);
      return ((double) int_value);
    case PLY_USHORT:
      pushort = (unsigned short int *) item;
      int_value = *pushort;
      fprintf (fp, "%d ", int_value);
      return ((double) int_value);
    case PLY_INT:
      pint = (int *) item;
      int_value = *pint;
      fprintf (fp, "%d ", int_value);
      return ((double) int_value);
    case PLY_UINT:
      puint = (unsigned int *) item;
      uint_value = *puint;
      fprintf (fp, "%u ", uint_value);
      return ((double) uint_value);
    case PLY_FLOAT:
      pfloat = (float *) item;
      double_value = *pfloat;
      fprintf (fp, "%g ", double_value);
      return (double_value);
    case PLY_DOUBLE:
      pdouble = (double *) item;
      double_value = *pdouble;
      fprintf (fp, "%g ", double_value);
      return (double_value);
    default:
      fprintf (stderr, "old_write_ascii_item: bad type = %d\n", type);
      exit (-1);
      return 0.0;
  }
}
