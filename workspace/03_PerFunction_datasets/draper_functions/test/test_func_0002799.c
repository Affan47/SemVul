vtkImageMedian3DAccumulateMedian(int &UpNum, int &DownNum,
                                         int &UpMax, int &DownMax,
                                         int &NumNeighborhood,
                                         double *Median, double val)
{
  int idx, max;
  double temp, *ptr;


  if (UpNum == 0)
    {
    *(Median) = val;

    UpNum = DownNum = 1;

    DownMax = UpMax = (NumNeighborhood + 1) / 2;
    return Median;
    }


  if (val >= *(Median))
    {

    if (UpNum > DownNum)
      {

      ++Median;
      --UpNum;
      ++DownNum;
      --UpMax;
      ++DownMax;
      }

    max = (UpNum < UpMax) ? UpNum : UpMax;
    ptr = Median;
    idx = 0;
    while (idx < max && val >= *ptr)
      {
      ++ptr;
      ++idx;
      }

    while (idx < max)
      {
      temp = *ptr;
      *ptr = val;
      val = temp;
      ++ptr;
      ++idx;
      }
    *ptr = val;

    ++UpNum;
    --DownMax;
    return Median;
    }


  if (DownNum > UpNum)
    {

    --Median;
    --DownNum;
    ++UpNum;
    --DownMax;
    ++UpMax;
    }

  max = (DownNum < DownMax) ? DownNum : DownMax;
  ptr = Median;
  idx = 0;
  while (idx < max && val <= *ptr)
    {
    --ptr;
    ++idx;
    }

  while (idx < max)
    {
    temp = *ptr;
    *ptr = val;
    val = temp;
    --ptr;
    ++idx;
    }
  *ptr = val;

  ++DownNum;
  --UpMax;

  return Median;
}
