gageStackBlurParmInit(gageStackBlurParm *parm) {

  if (parm) {
    parm->num = 0;
    parm->sigmaRange[0] = AIR_NAN;
    parm->sigmaRange[1] = AIR_NAN;
    parm->sigmaSampling = gageSigmaSamplingUnknown;
    parm->sigma = airFree(parm->sigma);
    parm->kspec = nrrdKernelSpecNix(parm->kspec);


    parm->renormalize = AIR_TRUE;
    parm->bspec = nrrdBoundarySpecNix(parm->bspec);
    parm->oneDim = AIR_FALSE;


    parm->needSpatialBlur = AIR_FALSE;
    parm->verbose = 1;
    parm->dgGoodSigmaMax = nrrdKernelDiscreteGaussianGoodSigmaMax;
  }
  return;
}
