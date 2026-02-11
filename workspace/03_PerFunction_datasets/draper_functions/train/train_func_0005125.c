Java_estraier_Database_set_1informer(JNIEnv *env, jobject obj, jobject informer){
  jclass cls;
  jfieldID fid;
  jlong coreptr;
  jobject oldobj;
  cls = (*env)->GetObjectClass(env, obj);
  fid = (*env)->GetFieldID(env, cls, "coreptr", "J");
  coreptr = (*env)->GetLongField(env, obj, fid);
  if(coreptr == 0){
    throwillarg(env);
    return;
  }
  fid = (*env)->GetFieldID(env, cls, "informer", "L" CLSDBINFO ";");
  if((oldobj = (*env)->GetObjectField(env, obj, fid)) != NULL)
    (*env)->DeleteGlobalRef(env, oldobj);
  (*env)->SetObjectField(env, obj, fid, NULL);
  if(!(informer = (*env)->NewGlobalRef(env, informer))){
    throwoutmem(env);
    return;
  }
  (*env)->SetObjectField(env, obj, fid, informer);
  infoenv = env;
  est_mtdb_set_informer((ESTMTDB *)(PTRNUM)coreptr, dbinform, informer);
}
