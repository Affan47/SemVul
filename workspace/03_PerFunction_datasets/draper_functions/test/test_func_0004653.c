drawCurve(double *samplebuf, int bsize, double max_val, double min_val, double *samplebuf2, int size2, double max_val2, double min_val2, int mrkr1, int mrkr2)
{
  buf1 = samplebuf;

  bufsize1 = bsize;

  max_value1 = max_val;

  min_value1 = min_val;

  buf2 = samplebuf2;

  bufsize2 = size2;

  max_value2 = max_val2;

  min_value2 = min_val2;

  if(mrkr1 > 0)
  {
    marker_1 = mrkr1;
  }
  else
  {
    marker_1 = 0;
  }

  if(mrkr2 > 0)
  {
    marker_2 = mrkr2;
  }
  else
  {
    marker_2 = 0;
  }

  update();
}
