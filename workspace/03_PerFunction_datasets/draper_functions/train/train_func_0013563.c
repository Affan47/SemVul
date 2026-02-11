Java_com_sun_grid_jgdi_jni_JGDIBaseImpl_nativeGetSGERoot(JNIEnv *env, jobject jgdi) {
   lList *alp = NULL;
   sge_gdi_ctx_class_t *ctx = NULL;
   const char *sge_root = NULL;
   jgdi_result_t ret = JGDI_SUCCESS;

   DENTER(JGDI_LAYER, "Java_com_sun_grid_jgdi_jni_JGDIBaseImpl_nativeGetSGERoot");

   if ((ret=getGDIContext(env, jgdi, &ctx, &alp)) != JGDI_SUCCESS) {
      throw_error_from_answer_list(env, ret, alp);
      lFreeList(&alp);
      DRETURN(NULL);
   }
   sge_root = ctx->get_sge_root(ctx);
   if (sge_root != NULL) {
      DRETURN((*env)->NewStringUTF(env, sge_root));
   }
   DRETURN(NULL);
}
