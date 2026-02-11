gt_SAIMakeReader(SuffixarrayFileInterface *sai, enum sfxDataRequest rtype)
{
  struct seqDataReader reader = { NULL, NULL};
  switch (rtype)
  {
  case SFX_REQUEST_SUFTAB:
    reader = gt_SAIMakeSufTabReader(sai);
    break;
  case SFX_REQUEST_BWTTAB:
    reader = gt_SAIMakeBWTReader(sai);
    break;
  default:
    fprintf(stderr, "error: unimplemented request: %d, %s: %d!\n", rtype,
            __FILE__, __LINE__);
    exit(GT_EXIT_PROGRAMMING_ERROR);
  }
  return reader;
}
