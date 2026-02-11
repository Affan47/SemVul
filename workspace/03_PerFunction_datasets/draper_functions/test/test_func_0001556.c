dc_setlcpvaluesofrunsortedrange(GtLcpvalues *samplelcpvalues,
                                            unsigned long blisbl,
                                            unsigned long width,
                                            unsigned long lcpvalue)
{
  unsigned long idx;

  for (idx = blisbl+1; idx < blisbl + width; idx++)
  {
    gt_lcptab_update(samplelcpvalues,0,idx,lcpvalue);
  }
}
