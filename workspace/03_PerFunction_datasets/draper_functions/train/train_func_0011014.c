is_supported_protocol (char **protocol)
{
  return protocol == DEFAULT_URI_PROTOCOL ||
         (str_equals (protocol [0], "tcp") &&
          str_equals (protocol [1], "none") &&
          str_equals (protocol [2], "xdr"));
}
