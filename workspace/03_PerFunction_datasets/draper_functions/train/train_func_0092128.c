tcase_create (const char *name)
{
  char *env;
  int timeout = DEFAULT_TIMEOUT;
  TCase *tc = emalloc (sizeof(TCase));
  if (name == NULL)
    tc->name = "";
  else
    tc->name = name;

  env = getenv("CK_DEFAULT_TIMEOUT");
  if (env != NULL) {
    int tmp = atoi(env);
    if (tmp >= 0) {
      timeout = tmp;
    }
  }

  tc->timeout = timeout;
  tc->tflst = check_list_create();
  tc->unch_sflst = check_list_create();
  tc->ch_sflst = check_list_create();
  tc->unch_tflst = check_list_create();
  tc->ch_tflst = check_list_create();

  return tc;
}
