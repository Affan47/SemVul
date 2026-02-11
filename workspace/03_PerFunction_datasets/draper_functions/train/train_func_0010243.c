gt_tyr_occratio_runner(GT_UNUSED int argc,
                                  GT_UNUSED const char **argv,
                                  GT_UNUSED int parsed_args,
                                  void *tool_arguments,
                                  GtError *err)
{
  GtLogger *logger;
  Tyr_occratio_options *arguments = tool_arguments;
  bool haserr = false;
  GtArrayuint64_t uniquedistribution,
                  nonuniquedistribution,
                  nonuniquemultidistribution;

  logger = gt_logger_new(arguments->verbose, GT_LOGGER_DEFLT_PREFIX, stdout);
  GT_INITARRAY(&uniquedistribution,uint64_t);
  GT_INITARRAY(&nonuniquedistribution,uint64_t);
  GT_INITARRAY(&nonuniquemultidistribution,uint64_t);
  if (gt_tyr_occratio_func(gt_str_get(arguments->str_inputindex),
                           arguments->scanfile,
                           arguments->minmersize,
                           arguments->maxmersize,
                           &uniquedistribution,
                           &nonuniquedistribution,
                           &nonuniquemultidistribution,
                           logger,
                           err) != 0)
  {
    haserr = true;
  }
  if (!haserr)
  {
    showoccratios(&uniquedistribution,
                  &nonuniquedistribution,
                  &nonuniquemultidistribution,
                  arguments->outputmode,
                  arguments->outputvector);
  }
  gt_logger_delete(logger);
  GT_FREEARRAY(&uniquedistribution,uint64_t);
  GT_FREEARRAY(&nonuniquedistribution,uint64_t);
  GT_FREEARRAY(&nonuniquemultidistribution,uint64_t);
  return haserr ? -1 : 0;
}
