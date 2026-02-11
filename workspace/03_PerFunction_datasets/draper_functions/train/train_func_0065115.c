gt_ltrharvest_stream_free(GtNodeStream *ns)
{
  GtLTRharvestStream *ltrh_stream = gt_ltrharvest_stream_cast(ns);
  GT_FREEARRAY(&ltrh_stream->arrayLTRboundaries, LTRboundaries);
  if (ltrh_stream->ssar != NULL)
    gt_freeSequentialsuffixarrayreader(&ltrh_stream->ssar);
  if (ltrh_stream->bdptrtab != NULL)
    gt_free(ltrh_stream->bdptrtab);
}
