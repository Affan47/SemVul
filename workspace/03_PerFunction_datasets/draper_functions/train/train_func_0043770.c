gt_encseq_show_features(const GtEncseq *encseq,
                             GtLogger *logger,
                             bool withfilenames)
{
  unsigned long idx;

  if (withfilenames)
  {
    for (idx = 0; idx < encseq->numofdbfiles; idx++)
    {
      gt_assert(encseq->filenametab != NULL);
      gt_logger_log(logger,"dbfile=%s " Formatuint64_t " " Formatuint64_t,
                     gt_str_array_get(encseq->filenametab,idx),
                PRINTuint64_tcast(encseq->headerptr.filelengthtab[idx].length),
                PRINTuint64_tcast(encseq->headerptr.filelengthtab[idx].
                                       effectivelength));
    }
  }
  gt_logger_log(logger,"totallength=%lu",
                       gt_encseq_total_length(encseq));
  gt_logger_log(logger,"numofsequences=%lu",encseq->logicalnumofdbsequences);
  gt_logger_log(logger,"specialcharacters=%lu",
                       gt_encseq_specialcharacters(encseq));
  gt_logger_log(logger,"specialranges=%lu",
                       gt_encseq_specialranges(encseq));
  gt_logger_log(logger,"realspecialranges=%lu",
                       gt_encseq_realspecialranges(encseq));
  gt_logger_log(logger,"wildcards=%lu",
                       gt_encseq_wildcards(encseq));
  gt_logger_log(logger,"wildcardranges=%lu",
                       gt_encseq_wildcardranges(encseq));
  gt_logger_log(logger,"realwildcardranges=%lu",
                       gt_encseq_realwildcardranges(encseq));

  gt_assert(encseq->headerptr.characterdistribution != NULL);
  showcharacterdistribution(encseq,logger);
}
