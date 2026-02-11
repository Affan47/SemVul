Java_com_sleepycat_db_internal_db_1javaJNI_Db_1join(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jobjectArray jarg2, jint jarg3) {
  jlong jresult = 0 ;
  struct Db *arg1 = (struct Db *) 0 ;
  DBC **arg2 = (DBC **) 0 ;
  u_int32_t arg3 ;
  DBC *result = 0 ;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct Db **)&jarg1;
  {
    int i, count, ret;

    count = (*jenv)->GetArrayLength(jenv, jarg2);
    if ((ret = __os_malloc(NULL, (count + 1) * sizeof(DBC *), &arg2)) != 0) {
      __dbj_throw(jenv, ret, NULL, NULL, DB2JDBENV);
      return 0;
    }
    for (i = 0; i < count; i++) {
      jobject jobj = (*jenv)->GetObjectArrayElement(jenv, jarg2, i);


      if (jobj == NULL) {
        arg2[i] = NULL;
        break;
      } else {
        jlong jptr = (*jenv)->GetLongField(jenv, jobj,
          dbc_cptr_fid);
        arg2[i] = *(DBC **)(void *)&jptr;
      }
    }
    arg2[count] = NULL;
  }
  arg3 = (u_int32_t)jarg3;

  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return 0;
  }

  errno = 0;
  result = (DBC *)Db_join(arg1,arg2,arg3);
  if (!DB_RETOK_STD(errno)) {
    __dbj_throw(jenv, errno, NULL, NULL, DB2JDBENV);
  }

  *(DBC **)&jresult = result;

  __os_free(NULL, arg2);

  return jresult;
}
