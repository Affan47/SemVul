maskTop16(void* p, int value, PIXEL_PARAMS* params)
{
  U16* newP = 0;

  int r = 0;
  int c = 0;

  newP = (U16*)p;

  for (r = params->rows/2; r < params->rows; r++) {
    for (c = 0; c < params->columns; c++) {
      newP[(r*params->columns) + c] = value;
    }
  }
}
