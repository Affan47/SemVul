gt_Outlcpinfo_nonspecialsbucket(GtOutlcpinfo *outlcpinfo,
                                     unsigned int prefixlength,
                                     const GtSuffixsortspace *sssp,
                                     GtLcpvalues *tableoflcpvalues,
                                     const GtBucketspecification *bucketspec,
                                     GtCodetype code)
{
  if (outlcpinfo != NULL)
  {
    unsigned long lcpvalue;
    Suffixwithcode firstsuffixofbucket;

    if (outlcpinfo->previoussuffix.defined)
    {


      firstsuffixofbucket.code = code;
      firstsuffixofbucket.prefixindex = prefixlength;
#ifdef SKDEBUG
      firstsuffixofbucket.startpos
        = gt_suffixsortspace_get(sssp,0,bucketspec->left);


#endif
      lcpvalue = computelocallcpvalue(&outlcpinfo->previoussuffix,
                                      &firstsuffixofbucket,
                                      outlcpinfo->minchanged);
    } else
    {

      lcpvalue = 0;
    }
    gt_lcptab_update(tableoflcpvalues,0,0,lcpvalue);

    if (outlcpinfo->lcpsubtab.lcp2file != NULL)
    {
      outlcpvalues(&outlcpinfo->lcpsubtab,
                   bucketspec->nonspecialsinbucket,
                   bucketspec->left);
    } else
    {
      if (outlcpinfo->lcpsubtab.lcpprocess != NULL)
      {
        outlcpinfo->lcpsubtab.lcpprocess->final_process_bucket(
            outlcpinfo->lcpsubtab.lcpprocess->final_process_bucket_info,
            sssp,
            tableoflcpvalues,
            0,
            bucketspec->nonspecialsinbucket,
            bucketspec->left);
      }
    }

    outlcpinfo->previoussuffix.code = code;
    outlcpinfo->previoussuffix.prefixindex = prefixlength;
#ifdef SKDEBUG
    outlcpinfo->previoussuffix.startpos
      = gt_suffixsortspace_get(sssp,0,
                               bucketspec->left
                                 + bucketspec->nonspecialsinbucket - 1);


#endif
  }
}
