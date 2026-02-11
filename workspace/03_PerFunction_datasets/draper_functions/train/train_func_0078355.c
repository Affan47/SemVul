InternalRequestUpdateExtent(int *inExt,
                                                         int *wholeExtent)
{
  int idx, radius;


  for (idx = 0; idx < this->Dimensionality; ++idx)
    {
    radius = static_cast<int>(this->StandardDeviations[idx]
                              * this->RadiusFactors[idx]);
    inExt[idx*2] -= radius;
    if (inExt[idx*2] < wholeExtent[idx*2])
      {
      inExt[idx*2] = wholeExtent[idx*2];
      }

    inExt[idx*2+1] += radius;
    if (inExt[idx*2+1] > wholeExtent[idx*2+1])
      {
      inExt[idx*2+1] = wholeExtent[idx*2+1];
      }
    }
}
