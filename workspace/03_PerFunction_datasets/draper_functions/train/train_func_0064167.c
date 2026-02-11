error_callback (const DB_ENV* dbe,
                            const char *errpfx, const char *msg)
#else
static void error_callback (const char *errpfx, char *msg)
#endif
{
  char *data;
  if (error_message) {
    int len = strlen(error_message);
    error_message = (char*)clisp_realloc(error_message,3 + strlen(msg) + len);
    error_message[len++] = ';';
    error_message[len++] = ' ';
    data = error_message + len;
  } else {
    int offset = errpfx ? strlen(errpfx)+4 : 0;
    data = error_message = (char*)clisp_malloc(1 + offset + strlen(msg));
    if (errpfx) {
      data[0] = '[';
      strcpy(data+1,errpfx);
      data[offset-3] = ']';
      data[offset-2] = ':';
      data[offset-1] = ' ';
    }
    data += offset;
  }
  strcpy(data,msg);
}
