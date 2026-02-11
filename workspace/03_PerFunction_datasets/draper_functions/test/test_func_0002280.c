Java_com_sleepycat_db_internal_db_1javaJNI_DbEnv_1lock_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3, jobject jarg4, jint jarg5) {
  jlong jresult = 0 ;
  struct DbEnv *arg1 = (struct DbEnv *) 0 ;
  u_int32_t arg2 ;
  u_int32_t arg3 ;
  DBT *arg4 = (DBT *) 0 ;
  db_lockmode_t arg5 ;
  DBT_LOCKED ldbt4 ;
  DB_LOCK *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct DbEnv **)&jarg1;
  arg2 = (u_int32_t)jarg2;
  arg3 = (u_int32_t)jarg3;

  if (__dbj_dbt_copyin(jenv, &ldbt4, &arg4, jarg4, 0) != 0) {
    return 0;
  }
  arg5 = (db_lockmode_t)jarg5;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return 0;
  }

  errno = 0;
  result = (DB_LOCK *)DbEnv_lock_get(arg1,arg2,arg3,arg4,arg5);
  if (!DB_RETOK_STD(errno)) {
    __dbj_throw(jenv, errno, NULL, NULL, JDBENV);
  }

  *(DB_LOCK **)&jresult = result;
  __dbj_dbt_release(jenv, jarg4, arg4, &ldbt4);
  return jresult;
}
