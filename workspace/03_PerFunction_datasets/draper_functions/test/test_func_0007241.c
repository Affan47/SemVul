ResolveVariablesRecursively(Scope* global_scope,
                                        Handle<Context> context) {
  ASSERT(global_scope == NULL || global_scope->is_global_scope());


  for (int i = 0; i < unresolved_.length(); i++) {
    ResolveVariable(global_scope, context, unresolved_[i]);
  }


  for (int i = 0; i < inner_scopes_.length(); i++) {
    inner_scopes_[i]->ResolveVariablesRecursively(global_scope, context);
  }
}
