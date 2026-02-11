sampling_io_header_samplingtab(GtSampling *sampling,
                                           FILE *fp,
                                           SamplingIOFunc io_func)
{
  sampling_io_header(sampling, fp, io_func);
  gt_assert(sampling->method == GT_SAMPLING_REGULAR ||
            sampling->method == GT_SAMPLING_PAGES);

  if (sampling->samplingtab == NULL) {
    sampling->arraysize = sampling->numofsamples;
    sampling->samplingtab = gt_malloc((size_t) sampling->arraysize *
                                        sizeof (*sampling->samplingtab));
  }
  sampling_io_samplingtab(sampling, fp, io_func);
}
