bc_gen_new_object_array(JVM_METHOD *meth, int size, char *class)
{
  JVM_CODE_GRAPH_NODE *node, *first;
  int c;
  char *tmp;

  if(!meth || !class) {
    BAD_ARG();
    return NULL;
  }

  first = NULL;

  if(size >= 0)
    first = bc_push_int_const(meth, size);

  tmp = char_substitute(class, '.', '/');

  if(!tmp) return NULL;

  c = cp_find_or_insert(meth->class, CONSTANT_Class, tmp);

  free(tmp);

  if(c < 0) return NULL;

  node = bytecode1(meth, jvm_anewarray, c);

  if(first)
    return first;
  else
    return node;
}
