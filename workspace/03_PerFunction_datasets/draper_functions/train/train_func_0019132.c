NewTemporary(Handle<String> name) {
  ASSERT(!already_resolved());
  Variable* var = new Variable(this,
                               name,
                               Variable::TEMPORARY,
                               true,
                               Variable::NORMAL);
  temps_.Add(var);
  return var;
}
