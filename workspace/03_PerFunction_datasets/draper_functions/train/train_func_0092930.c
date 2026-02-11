set_string_arg(const char *value)
{
  switch (_type)
    {
    case CMD_ARG_LONG:
      _val.v_long = strtol(value, NULL, 0);
      break;
    case CMD_ARG_STRING:
      _val.v_string = strdup(value);
      break;
    }
  _value_set = true;
}
