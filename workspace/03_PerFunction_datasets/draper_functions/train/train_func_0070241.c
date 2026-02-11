Java_com_sleepycat_db_internal_db_1javaJNI_Db_1cursor(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_, jint jarg3) {
  jlong jresult = 0 ;
  struct Db *arg1 = (struct Db *) 0 ;
  DB_TXN *arg2 = (DB_TXN *) 0 ;
  u_int32_t arg3 ;
  DBC *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(struct Db **)&jarg1;
  arg2 = *(DB_TXN **)&jarg2;
  arg3 = (u_int32_t)jarg3;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return 0;
  }

  errno = 0;
  result = (DBC *)Db_cursor(arg1,arg2,arg3);
  if (!DB_RETOK_STD(errno)) {
    __dbj_throw(jenv, errno, NULL, NULL, DB2JDBENV);
  }

  *(DBC **)&jresult = result;
  return jresult;
}
