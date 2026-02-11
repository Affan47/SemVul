check_own_socket (void)
{
  char *sockname;
  pth_attr_t tattr;

  if (!opt.use_standard_socket)
    return;

  if (check_own_socket_running || shutdown_pending)
    return;

  sockname = make_filename (opt.homedir, "S.gpg-agent", NULL);
  if (!sockname)
    return;

  tattr = pth_attr_new();
  pth_attr_set (tattr, PTH_ATTR_JOINABLE, 0);
  pth_attr_set (tattr, PTH_ATTR_STACK_SIZE, 256*1024);
  pth_attr_set (tattr, PTH_ATTR_NAME, "check-own-socket");

  if (!pth_spawn (tattr, check_own_socket_thread, sockname))
      log_error ("error spawning check_own_socket_thread: %s\n",
                 strerror (errno) );
  pth_attr_destroy (tattr);
}
