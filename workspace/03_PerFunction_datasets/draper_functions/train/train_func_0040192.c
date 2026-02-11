get_remote_host_and_port_from_config(
char **hostname,
int *port,
dstring *err_msg)
{
   char *address;
   char *separator;

   if (err_msg == NULL) {
      return 1;
   }

   address = get_conf_val("qrsh_control_port");
   if (address == NULL) {
      sge_dstring_sprintf(err_msg, "config does not contain entry for qrsh_control_port");
      return 2;
   }


   address = strdup(address);
   separator = strchr(address, ':');
   if (separator == NULL) {
      sge_dstring_sprintf(err_msg, "illegal value for qrsh_control_port: "
                        "\"%s\". Should be host:port", address);
      FREE(address);
      return 3;
   }

   *separator = '\0';
   *hostname = address;
   *port = atoi(separator + 1);

   return 0;
}
