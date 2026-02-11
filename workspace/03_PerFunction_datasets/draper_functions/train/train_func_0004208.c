tenFiberKernelSet(tenFiberContext *tfx,
                  const NrrdKernel *kern,
                  const double parm[NRRD_KERNEL_PARMS_NUM]) {
  static const char me[]="tenFiberKernelSet";

  if (!(tfx && kern)) {
    biffAddf(TEN, "%s: got NULL pointer", me);
    return 1;
  }
  nrrdKernelSpecSet(tfx->ksp, kern, parm);
  if (gageKernelSet(tfx->gtx, gageKernel00,
                    tfx->ksp->kernel, tfx->ksp->parm)) {
    biffMovef(TEN, GAGE, "%s: problem setting kernel", me);
    return 1;
  }

  return 0;
}
