SWIG_Perl_TypeProxyName(const swig_type_info *type) {
  if (!type) return NULL;
  if (type->clientdata != NULL) {
    return (const char*) type->clientdata;
  }
  else {
    return type->name;
  }
}
