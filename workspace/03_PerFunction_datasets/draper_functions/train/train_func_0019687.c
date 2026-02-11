Java_com_sleepycat_db_internal_db_1javaJNI_DbSequence_1stat(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jobject jresult = 0 ;
  struct DbSequence *arg1 = (struct DbSequence *) 0 ;
  u_int32_t arg2 ;
  DB_SEQUENCE_STAT *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct DbSequence **)&jarg1;
  arg2 = (u_int32_t)jarg2;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return 0;
  }

  errno = 0;
  result = (DB_SEQUENCE_STAT *)DbSequence_stat(arg1,arg2);
  if (!DB_RETOK_STD(errno)) {
    __dbj_throw(jenv, errno, NULL, NULL, NULL);
  }


  if (result == NULL)
  jresult = NULL;
  else {
    jresult = (*jenv)->NewObject(jenv, seq_stat_class, seq_stat_construct);
    if (jresult != NULL)
    __dbj_fill_seq_stat(jenv, jresult, result);
    __os_ufree(NULL, result);
  }

  return jresult;
}
