Java_com_sleepycat_db_internal_db_1javaJNI_Dbc_1set_1priority(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  struct Dbc *arg1 = (struct Dbc *) 0 ;
  DB_CACHE_PRIORITY arg2 ;
  db_ret_t result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct Dbc **)&jarg1;
  arg2 = (DB_CACHE_PRIORITY)jarg2;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return ;
  }

  errno = 0;
  result = (db_ret_t)Dbc_set_priority(arg1,arg2);
  if (!DB_RETOK_STD(errno)) {
    __dbj_throw(jenv, errno, NULL, NULL, DBC2JDBENV);
  }

}
