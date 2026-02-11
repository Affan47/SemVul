Java_org_jblas_NativeBlas_icamax(JNIEnv *env, jclass this, jint n, jfloatArray cx, jint cxIdx, jint incx)
{
  extern jint icamax_(jint *, jfloat *, jint *);

  jfloat *cxPtrBase = 0, *cxPtr = 0;
  if (cx) {
    cxPtrBase = (*env)->GetFloatArrayElements(env, cx, NULL);
    cxPtr = cxPtrBase + 2*cxIdx;
  }

  savedEnv = env;
  jint retval = icamax_(&n, cxPtr, &incx);
  if(cxPtrBase) {
    (*env)->ReleaseFloatArrayElements(env, cx, cxPtrBase, 0);
    cxPtrBase = 0;
  }

  return retval;
}
