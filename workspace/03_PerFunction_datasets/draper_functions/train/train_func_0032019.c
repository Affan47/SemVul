bcwrite_knum(BCWriteCtx *ctx, GCproto *pt)
{
  MSize i, sizekn = pt->sizekn;
  cTValue *o = mref(pt->k, TValue);
  bcwrite_need(ctx, 10*sizekn);
  for (i = 0; i < sizekn; i++, o++) {
    int32_t k;
    if (tvisint(o)) {
      k = intV(o);
      goto save_int;
    } else {

      if (!LJ_DUALNUM) {
	lua_Number num = numV(o);
	k = lj_num2int(num);
	if (num == (lua_Number)k) {
	save_int:
	  bcwrite_uleb128(ctx, 2*(uint32_t)k | ((uint32_t)k & 0x80000000u));
	  if (k < 0) {
	    char *p = &ctx->sb.buf[ctx->sb.n-1];
	    *p = (*p & 7) | ((k>>27) & 0x18);
	  }
	  continue;
	}
      }
      bcwrite_uleb128(ctx, 1+(2*o->u32.lo | (o->u32.lo & 0x80000000u)));
      if (o->u32.lo >= 0x80000000u) {
	char *p = &ctx->sb.buf[ctx->sb.n-1];
	*p = (*p & 7) | ((o->u32.lo>>27) & 0x18);
      }
      bcwrite_uleb128(ctx, o->u32.hi);
    }
  }
}
