gt_packedindex_chk_integrity(int argc, const char *argv[], GtError *err)
{
  struct encIdxSeq *seq;
  struct chkIndexOptions params;
  const char *inputProject;
  int parsedArgs;
  int had_err = 0;
  GtLogger *logger = NULL;
  gt_error_check(err);

  switch (parseChkIndexOptions(&parsedArgs, argc, argv, &params, err))
  {
    case GT_OPTION_PARSER_OK:
      break;
    case GT_OPTION_PARSER_ERROR:
      return -1;
    case GT_OPTION_PARSER_REQUESTS_EXIT:
      return 0;
  }

  inputProject = argv[parsedArgs];

  logger = gt_logger_new(params.verboseOutput, GT_LOGGER_DEFLT_PREFIX, stdout);

  seq = gt_loadEncIdxSeq(inputProject, params.encType, params.EISFeatureSet,
                      logger, err);
  if ((had_err = seq == NULL))
  {
    gt_error_set(err, "Failed to load index: %s", inputProject);
  }
  else
  {
    fprintf(stderr, "# Using index over sequence %lu"
            " symbols long.\n", EISLength(seq));
    {
      int corrupt
        = gt_EISVerifyIntegrity(seq, inputProject, params.skipCount,
                             params.progressInterval, stderr,
                             params.checkFlags, logger, err);
      if ((had_err = corrupt != 0))
      {
        fputs(gt_error_get(err), stderr); fputs("\n", stderr);
        gt_error_set(err, "Integrity check failed for index: %s",
                  EISIntegrityCheckResultStrings[corrupt]);
      }
    }
  }
  if (seq) gt_deleteEncIdxSeq(seq);
  if (logger) gt_logger_delete(logger);
  return had_err?-1:0;
}
