ccall_struct_reg(CCallState *cc, GPRArg *dp, int *rcl)
{
  MSize ngpr = cc->ngpr, nfpr = cc->nfpr;
  uint32_t i;
  for (i = 0; i < 2; i++) {
    lua_assert(!(rcl[i] & CCALL_RCL_MEM));
    if ((rcl[i] & CCALL_RCL_INT)) {
      if (ngpr >= CCALL_NARG_GPR) return 1;
      cc->gpr[ngpr++] = dp[i];
    } else if ((rcl[i] & CCALL_RCL_SSE)) {
      if (nfpr >= CCALL_NARG_FPR) return 1;
      cc->fpr[nfpr++].l[0] = dp[i];
    }
  }
  cc->ngpr = ngpr; cc->nfpr = nfpr;
  return 0;
}
