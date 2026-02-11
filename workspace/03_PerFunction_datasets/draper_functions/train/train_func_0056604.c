LCL_MakeStep(double threshold)
{
  struct timeval raw;
  double correction;

  LCL_ReadRawTime(&raw);
  LCL_GetOffsetCorrection(&raw, &correction, NULL);

  if (fabs(correction) <= threshold)
    return 0;


  LCL_AccumulateOffset(correction, 0.0);
  LCL_ApplyStepOffset(-correction);

  LOG(LOGS_WARN, LOGF_Local, "System clock was stepped by %.3f seconds", correction);

  return 1;
}
