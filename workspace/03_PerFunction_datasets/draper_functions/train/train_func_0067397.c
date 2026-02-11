FRadixSort(vtkHAVSSortedFace *array, vtkHAVSSortedFace *temp, int lo, int up)
{
  register int len = up-lo;
  register unsigned int i;
  register unsigned int u;

  vtkHAVSSortedFace * uints = array + lo;

  int count[4][256] = {{0}};


  for (i=0; i<(unsigned int)len; i++)
    {
    u = uints[i].Distance;
    count[0][u & 0xff]++;
    count[1][(u >> 8) & 0xff]++;
    count[2][(u >> 16) & 0xff]++;
    count[3][(u >> 24) & 0xff]++;
    }


  this->FRadix(0, len, uints, temp, count[0]);
  this->FRadix(1, len, temp, uints, count[1]);
  this->FRadix(2, len, uints, temp, count[2]);
  this->FRadix(3, len, temp, uints, count[3]);
}
