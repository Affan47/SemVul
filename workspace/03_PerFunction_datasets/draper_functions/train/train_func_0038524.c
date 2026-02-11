Java_com_sleepycat_db_internal_db_1javaJNI_DbEnv_1lock_1detect(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3) {
  jint jresult = 0 ;
  struct DbEnv *arg1 = (struct DbEnv *) 0 ;
  u_int32_t arg2 ;
  u_int32_t arg3 ;
  int result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct DbEnv **)&jarg1;
  arg2 = (u_int32_t)jarg2;
  arg3 = (u_int32_t)jarg3;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return 0;
  }

  errno = 0;
  result = (int)DbEnv_lock_detect(arg1,arg2,arg3);
  if (!DB_RETOK_STD(errno)) {
    __dbj_throw(jenv, errno, NULL, NULL, JDBENV);
  }

  jresult = (jint)result;
  return jresult;
}
