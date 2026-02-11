negation() {
  if (nav[idx] && !strcmp(nav[idx], "!")) {
    skip();
    return build(not, grouping(), (Expr) NULL);
  }
  else
    return grouping();
}
