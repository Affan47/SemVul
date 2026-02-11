exit_vecs(void)
{
  vecs_t *vec = vec_list;
  while (vec->vec) {
    arglist_t *ap;
    if (vec->vec->exit) {
      (*vec->vec->exit)();
    }
    if (vec->vec->args) {
      for (ap = vec->vec->args; ap->argstring; ap++) {
        if (ap->defaultvalue &&
            (ap->argtype == ARGTYPE_INT) &&
            ! is_integer(ap->defaultvalue)) {
          warning("%s: not an integer\n", ap->argstring);
        }
        if (ap->argvalptr) {
          xfree(ap->argvalptr);
          *ap->argval = ap->argvalptr = NULL;
        }
      }
    }
    vec++;
  }
}
