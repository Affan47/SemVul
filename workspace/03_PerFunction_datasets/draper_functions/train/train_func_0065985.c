ladish_client_set_jack_name(ladish_client_handle client_handle, const char * jack_name)
{
  char * name_dup;

  name_dup = strdup(jack_name);
  if (name_dup == NULL)
  {
    log_error("stdup(\"%s\") failed", jack_name);
    return;
  }

  free(client_ptr->jack_name);
  client_ptr->jack_name = name_dup;
}
