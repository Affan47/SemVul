get_opttype_str(OptionStr *confdata, short type)
{
  int i;
  for (i = 0; confdata[i].name != NULL; i++) {
    if (confdata[i].type == type) {
      return(confdata[i].name);
    }
  }
  rderr("unknown typecode in header!");
  return(NULL);
}
