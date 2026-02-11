emit_children(Node *n) {
  Node *c;
  char *eo = Char(Getattr(n, "feature:emitonlychildren"));
  for (c = firstChild(n); c; c = nextSibling(c)) {
    if (eo) {
      const char *tag = Char(nodeType(c));
      if (strcmp(tag, "cdecl") == 0) {
	if (checkAttribute(c, "storage", "typedef"))
	  tag = "typedef";
      }
      if (strstr(eo, tag) == 0) {
	continue;
      }
    }
    emit_one(c);
  }
  return SWIG_OK;
}
