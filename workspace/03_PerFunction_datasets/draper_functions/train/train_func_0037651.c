add(struct cvm_credential* creds,
		    unsigned i, unsigned type, const char* value)
{
  if (value == 0)
    return i;
  if (value[0] == 0)
    return i;
  creds[i].type = type;
  if (!str_copys(&creds[i].value, value))
    return 0;
  return i + 1;
}
