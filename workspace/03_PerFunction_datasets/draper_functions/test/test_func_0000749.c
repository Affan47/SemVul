gageKernelReset(gageContext *ctx) {

  int i;

  if (ctx) {
    for(i=gageKernelUnknown+1; i<gageKernelLast; i++) {
      ctx->ksp[i] = nrrdKernelSpecNix(ctx->ksp[i]);
    }
    ctx->flag[gageCtxFlagKernel] = AIR_TRUE;
  }
  return;
}
