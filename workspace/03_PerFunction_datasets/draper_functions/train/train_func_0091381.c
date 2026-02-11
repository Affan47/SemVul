make_ith_pack_parameter_name (tree name, int i)
{

#define NUMBUF_LEN 128
  char numbuf[NUMBUF_LEN];
  char* newname;
  int newname_len;

  if (name == NULL_TREE)
    return name;
  snprintf (numbuf, NUMBUF_LEN, "%i", i);
  newname_len = IDENTIFIER_LENGTH (name)
	        + strlen (numbuf) + 2;
  newname = (char*)alloca (newname_len);
  snprintf (newname, newname_len,
	    "%s#%i", IDENTIFIER_POINTER (name), i);
  return get_identifier (newname);
}
