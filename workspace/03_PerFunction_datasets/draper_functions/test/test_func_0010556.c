open_connection(void)
{
#ifdef _WIN32


  int oldvalue, oldvaluelen, newvalue, retcode;
  oldvaluelen = sizeof(oldvalue);
  retcode = getsockopt(INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE,
                       (char *) &oldvalue, &oldvaluelen);
  if (retcode == 0) {
      newvalue = SO_SYNCHRONOUS_NONALERT;
      setsockopt(INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE,
                 (char *) &newvalue, sizeof(newvalue));
  }
#endif
  dbg_socket = socket(sock_domain, SOCK_STREAM, 0);
#ifdef _WIN32
  if (retcode == 0) {

    setsockopt(INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE,
               (char *) &oldvalue, oldvaluelen);
  }
#endif
  if (dbg_socket == -1 ||
      connect(dbg_socket, &sock_addr.s_gen, sock_addr_len) == -1){
    caml_fatal_error_arg2 ("cannot connect to debugger at %s\n", dbg_addr,
                           "error: %s\n", strerror (errno));
  }
#ifdef _WIN32
  dbg_socket = _open_osfhandle(dbg_socket, 0);
  if (dbg_socket == -1)
    caml_fatal_error("_open_osfhandle failed");
#endif
  dbg_in = caml_open_descriptor_in(dbg_socket);
  dbg_out = caml_open_descriptor_out(dbg_socket);
  if (!caml_debugger_in_use) caml_putword(dbg_out, -1);
#ifdef _WIN32
  caml_putword(dbg_out, _getpid());
#else
  caml_putword(dbg_out, getpid());
#endif
  caml_flush(dbg_out);
}
