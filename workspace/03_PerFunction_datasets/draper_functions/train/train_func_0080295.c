Lookup(Handle<String> name) {
  for (Scope* scope = this;
       scope != NULL;
       scope = scope->outer_scope()) {
    Variable* var = scope->LocalLookup(name);
    if (var != NULL) return var;
  }
  return NULL;
}
