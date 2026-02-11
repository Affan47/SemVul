insert_string_constant(JVM_CLASS *class, const void *val, BOOL force_insert) {
  CP_INFO * newnode;
  int idx;

  if(!class || !val)  {
    BAD_ARG();
    return -1;
  }


  debug_msg("inserting a string... '%s'\n",(char *)val);

  idx = cp_lookup(class, CONSTANT_Utf8, val);

  if(idx < 0)
  {

    debug_msg("&& in insert_constant, inserting '%s'\n",(char *)val);

    newnode = (CP_INFO *)malloc(sizeof(CP_INFO));
    if(!newnode) return -1;

    newnode->tag = CONSTANT_Utf8;
    newnode->cpnode.Utf8.length = strlen(val);
    newnode->cpnode.Utf8.bytes = (u1 *) malloc(newnode->cpnode.Utf8.length);
    if(!newnode->cpnode.Utf8.bytes) {
      free(newnode);
      return -1;
    }

    strncpy((char *)newnode->cpnode.Utf8.bytes, val,
        newnode->cpnode.Utf8.length);

    idx = cp_insert(class, newnode);
  }
  else if(idx == 0) {
    debug_err("WARNING insert_constant(): idx is 0\n");
  }

  newnode = (CP_INFO *)malloc(sizeof(CP_INFO));
  if(!newnode) return -1;

  newnode->tag = CONSTANT_String;
  newnode->cpnode.String.string_index = (u2)idx;

  return cp_insert(class, newnode);
}
