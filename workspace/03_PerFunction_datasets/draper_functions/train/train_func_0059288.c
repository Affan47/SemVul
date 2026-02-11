Java_com_sleepycat_db_internal_db_1javaJNI_Db_1set_1h_1compare(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jboolean jarg2) {
  struct Db *arg1 = (struct Db *) 0 ;
  int (*arg2)(DB *,DBT const *,DBT const *,size_t *) = (int (*)(DB *,DBT const *,DBT const *,size_t *)) 0 ;
  db_ret_t result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct Db **)&jarg1;

  arg2 = (jarg2 == JNI_TRUE) ? __dbj_h_compare : NULL;


  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return ;
  }

  result = (db_ret_t)Db_set_h_compare(arg1,arg2);
  if (!DB_RETOK_STD(result)) {
    __dbj_throw(jenv, result, NULL, NULL, DB2JDBENV);
  }

}
