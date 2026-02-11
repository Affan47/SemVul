AllocateNonParameterLocals() {

  for (int i = 0; i < temps_.length(); i++) {
    AllocateNonParameterLocal(temps_[i]);
  }

  for (VariableMap::Entry* p = variables_.Start();
       p != NULL;
       p = variables_.Next(p)) {
    Variable* var = reinterpret_cast<Variable*>(p->value);
    AllocateNonParameterLocal(var);
  }


  if (function_ != NULL) {
    AllocateNonParameterLocal(function_);
  }
}
