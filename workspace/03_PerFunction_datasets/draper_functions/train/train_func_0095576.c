camMotionEstimation3DRSInit(CamMotionEstimation3DRSParams *params, int seed, int lsearch, int rsearch, int bs, int scans, int candidates, int test0)
{
    params->niter=0;
    params->seed=seed;
    params->lsearch=lsearch;
    params->rsearch=rsearch;
    if ((bs!=8)&&(bs!=16)) return 0;
    params->blockSize=bs;
    params->scans=scans;
    if (candidates>MAX_CANDIDATES) return 0;
    params->candidates=candidates;
    params->test0=test0;
    return 1;
}
