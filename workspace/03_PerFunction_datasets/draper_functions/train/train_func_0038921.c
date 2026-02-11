Java_com_sleepycat_db_internal_db_1javaJNI_DbEnv_1repmgr_1channel(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3) {
  jlong jresult = 0 ;
  struct DbEnv *arg1 = (struct DbEnv *) 0 ;
  int arg2 ;
  u_int32_t arg3 ;
  DB_CHANNEL *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct DbEnv **)&jarg1;
  arg2 = (int)jarg2;
  arg3 = (u_int32_t)jarg3;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return 0;
  }

  errno = 0;
  result = (DB_CHANNEL *)DbEnv_repmgr_channel(arg1,arg2,arg3);
  if (!DB_RETOK_STD(errno)) {
    __dbj_throw(jenv, errno, NULL, NULL, JDBENV);
  }

  *(DB_CHANNEL **)&jresult = result;
  return jresult;
}
