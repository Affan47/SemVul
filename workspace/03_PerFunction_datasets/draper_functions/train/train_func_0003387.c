Java_com_sleepycat_db_internal_db_1javaJNI_DbSequence_1remove0(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_, jint jarg3) {
  struct DbSequence *arg1 = (struct DbSequence *) 0 ;
  DB_TXN *arg2 = (DB_TXN *) 0 ;
  u_int32_t arg3 ;
  db_ret_t result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(struct DbSequence **)&jarg1;
  arg2 = *(DB_TXN **)&jarg2;
  arg3 = (u_int32_t)jarg3;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return ;
  }

  result = (db_ret_t)DbSequence_remove(arg1,arg2,arg3);
  if (!DB_RETOK_STD(result)) {
    __dbj_throw(jenv, result, NULL, NULL, NULL);
  }

}
