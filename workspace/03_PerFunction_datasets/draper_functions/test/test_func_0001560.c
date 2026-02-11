proxy_error_function(const String &h, void *thunk)
{
  ControlSocket *cs = static_cast<ControlSocket *>(thunk);
  return (h == cs->_proxied_handler ? cs->_proxied_errh : 0);
}
