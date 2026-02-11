Java_com_sleepycat_db_internal_db_1javaJNI_DbEnv_1lock_1put(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  struct DbEnv *arg1 = (struct DbEnv *) 0 ;
  DB_LOCK *arg2 = (DB_LOCK *) 0 ;
  db_ret_t result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(struct DbEnv **)&jarg1;
  arg2 = *(DB_LOCK **)&jarg2;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return ;
  }

  result = (db_ret_t)DbEnv_lock_put(arg1,arg2);
  if (!DB_RETOK_STD(result)) {
    __dbj_throw(jenv, result, NULL, NULL, JDBENV);
  }

}
