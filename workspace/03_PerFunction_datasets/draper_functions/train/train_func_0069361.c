close_lisp_socket (lisp_cfg_t * cfg)
{
  if (SERVER_SOCKET (cfg))
    {
      RELAY_ERROR (apr_socket_close (SERVER_SOCKET (cfg)));
      (SERVER_SOCKET (cfg)) = 0;
    }
  return (APR_SUCCESS);
}
