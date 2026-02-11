classHandler(Node *n) {
#ifdef ALLEGROCL_DEBUG
  Printf(stderr, "classHandler %s::%s\n", current_namespace, Getattr(n, "sym:name"));
#endif

  int result;

  if (Generate_Wrapper)
    result = cppClassHandler(n);
  else
    result = cClassHandler(n);

  return result;
}
