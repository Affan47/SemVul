Java_com_sleepycat_db_internal_db_1javaJNI_DbEnv_1rep_1elect(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3, jint jarg4) {
  struct DbEnv *arg1 = (struct DbEnv *) 0 ;
  u_int32_t arg2 ;
  int arg3 ;
  u_int32_t arg4 ;
  db_ret_t result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct DbEnv **)&jarg1;
  arg2 = (u_int32_t)jarg2;
  arg3 = (int)jarg3;
  arg4 = (u_int32_t)jarg4;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return ;
  }

  result = (db_ret_t)DbEnv_rep_elect(arg1,arg2,arg3,arg4);
  if (!DB_RETOK_STD(result)) {
    __dbj_throw(jenv, result, NULL, NULL, JDBENV);
  }

}
