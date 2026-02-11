readKeyValue (char *string, char *key, char *format, void *value)
  {

    if (! (string = strstr(string, key)))  return FALSE;
    string += strlen(key);
    if (! (string = strchr(string, '=')))  return FALSE;
    string++;
    return  sscanf(string, format, value);
  }
