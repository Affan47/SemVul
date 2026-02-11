some_object_hello_world (SomeObject *obj, const char *hello_message, char ***ret, GError **error)
{
  printf ("%s\n", hello_message);
  *ret = g_new (char *, 3);
  (*ret)[0] = g_strdup ("Hello");
  (*ret)[1] = g_strdup (" from example-service.c");
  (*ret)[2] = NULL;

  return TRUE;
}
