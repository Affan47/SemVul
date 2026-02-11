Java_com_sleepycat_db_internal_db_1javaJNI_DbEnv_1get_1mp_1max_1write_1sleep(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  struct DbEnv *arg1 = (struct DbEnv *) 0 ;
  db_timeout_t result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct DbEnv **)&jarg1;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return 0;
  }

  errno = 0;
  result = (db_timeout_t)DbEnv_get_mp_max_write_sleep(arg1);
  if (!DB_RETOK_STD(errno)) {
    __dbj_throw(jenv, errno, NULL, NULL, JDBENV);
  }

  jresult = (jlong)result;
  return jresult;
}
