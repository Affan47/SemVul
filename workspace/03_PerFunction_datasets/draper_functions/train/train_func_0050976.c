concatenation() {
  Expr left;
  char *this;

  left = negation ();
  this = nav[idx];
  if (this && (!strcmp(this, "-a") || !strcmp(this, "!") ||
	       !strcmp(this, "(") || (*this == '-' && strcmp(this, "-o")))){
    if (!strcmp(this, "-a")) skip();
    return build(and, left, concatenation());
  }
  else
    return left;
}
