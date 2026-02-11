item_size(Type *type, int dim) {
  if(dim < type->dimensions) {
    return SIZE_P;
  } else {
    switch(type->type) {
      case TK_TINT: return SIZE_INT;
      case TK_TCHAR: return SIZE_CHAR;
    }
  }
}
