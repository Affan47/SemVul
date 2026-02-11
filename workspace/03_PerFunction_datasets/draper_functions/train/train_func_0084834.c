objtocblist(JNIEnv *env, jobject obj){
  jclass list, it;
  jmethodID midit, midhn, midn;
  jobject itobj, eobj;
  jboolean icelem;
  CBLIST *tlist;
  const char *telem;
  assert(obj);
  tlist = cblistopen();
  list = (*env)->GetObjectClass(env, obj);
  midit = (*env)->GetMethodID(env, list, "iterator", "()L" CLSITERATOR ";");
  itobj = (*env)->CallObjectMethod(env, obj, midit);
  it = (*env)->GetObjectClass(env, itobj);
  midhn = (*env)->GetMethodID(env, it, "hasNext", "()Z");
  midn = (*env)->GetMethodID(env, it, "next", "()L" CLSOBJECT ";");
  while((*env)->CallBooleanMethod(env, itobj, midhn)){
    eobj = (*env)->CallObjectMethod(env, itobj, midn);
    if(!isinstanceof(env, eobj, CLSSTRING)) continue;
    if(!(telem = (*env)->GetStringUTFChars(env, eobj, &icelem))) continue;
    cblistpush(tlist, telem, -1);
    if(icelem == JNI_TRUE) (*env)->ReleaseStringUTFChars(env, eobj, telem);
  }
  return tlist;
}
