Java_com_sleepycat_db_internal_db_1javaJNI_DbEnv_1set_1lg_1max(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  struct DbEnv *arg1 = (struct DbEnv *) 0 ;
  u_int32_t arg2 ;
  db_ret_t result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct DbEnv **)&jarg1;
  arg2 = (u_int32_t)jarg2;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return ;
  }

  result = (db_ret_t)DbEnv_set_lg_max(arg1,arg2);
  if (!DB_RETOK_STD(result)) {
    __dbj_throw(jenv, result, NULL, NULL, JDBENV);
  }

}
