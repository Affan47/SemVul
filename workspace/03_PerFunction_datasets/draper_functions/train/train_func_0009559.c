Java_org_jblas_NativeBlas_cdotu(JNIEnv *env, jclass this, jint n, jfloatArray cx, jint cxIdx, jint incx, jfloatArray cy, jint cyIdx, jint incy)
{
  extern float complex cdotu_(jint *, jfloat *, jint *, jfloat *, jint *);

  jfloat *cxPtrBase = 0, *cxPtr = 0;
  if (cx) {
    cxPtrBase = (*env)->GetFloatArrayElements(env, cx, NULL);
    cxPtr = cxPtrBase + 2*cxIdx;
  }
  jfloat *cyPtrBase = 0, *cyPtr = 0;
  if (cy) {
    if((*env)->IsSameObject(env, cy, cx) == JNI_TRUE)
      cyPtrBase = cxPtrBase;
    else
      cyPtrBase = (*env)->GetFloatArrayElements(env, cy, NULL);
    cyPtr = cyPtrBase + 2*cyIdx;
  }

  savedEnv = env;
  float complex retval = cdotu_(&n, cxPtr, &incx, cyPtr, &incy);
  if(cyPtrBase) {
    (*env)->ReleaseFloatArrayElements(env, cy, cyPtrBase, 0);
    if (cyPtrBase == cxPtrBase)
      cxPtrBase = 0;
    cyPtrBase = 0;
  }
  if(cxPtrBase) {
    (*env)->ReleaseFloatArrayElements(env, cx, cxPtrBase, 0);
    cxPtrBase = 0;
  }

  return createComplexFloat(env, retval);
}
