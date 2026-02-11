SWIG_TypeCheck(const char *c, swig_type_info *ty) {
  if (ty) {
    swig_cast_info *iter = ty->cast;
    while (iter) {
      if (strcmp(iter->type->name, c) == 0) {
        if (iter == ty->cast)
          return iter;

        iter->prev->next = iter->next;
        if (iter->next)
          iter->next->prev = iter->prev;
        iter->next = ty->cast;
        iter->prev = 0;
        if (ty->cast) ty->cast->prev = iter;
        ty->cast = iter;
        return iter;
      }
      iter = iter->next;
    }
  }
  return 0;
}
