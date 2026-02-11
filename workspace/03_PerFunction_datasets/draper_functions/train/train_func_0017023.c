net_send(int sock, const char *message, ...) {
  struct sockinfo *sockinfo;

  sockinfo = _net_fetch(sock);
  if (sockinfo) {
    int ret = 0;
    va_list ap;
    char *msg;

    va_start(ap, message);
    msg = x_vsprintf(message, ap);
    va_end(ap);

    ret = _net_buffer(sockinfo, SB_OUT, SM_PACK, msg, strlen(msg));

    free(msg);
    return ret;
  } else {
    syscall_fail("net_send", 0, "bad socket provided");
    return -1;
  }
}
