baculaSetValue(bpContext *ctx, bwDirVariable var, void *value)
{
   JCR *jcr;
   if (!value || !ctx) {
      return bRC_Error;
   }

   jcr = ((bacula_ctx *)ctx->bContext)->jcr;
   if (!jcr) {
      return bRC_Error;
   }


   Dmsg1(dbglvl, "dir-plugin: baculaSetValue var=%d\n", var);
   return bRC_OK;
}
