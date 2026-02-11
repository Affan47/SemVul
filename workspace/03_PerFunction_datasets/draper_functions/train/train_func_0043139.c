GWEN_CTF_Context_new() {
  GWEN_CRYPT_TOKEN_CONTEXT *ctx;
  GWEN_CTF_CONTEXT *fctx;

  ctx=GWEN_Crypt_Token_Context_new();
  GWEN_NEW_OBJECT(GWEN_CTF_CONTEXT, fctx)
  GWEN_INHERIT_SETDATA(GWEN_CRYPT_TOKEN_CONTEXT, GWEN_CTF_CONTEXT, ctx, fctx,
		       GWEN_CTF_Context_freeData)

  return ctx;
}
