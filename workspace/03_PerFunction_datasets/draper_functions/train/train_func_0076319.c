PushVariableName(Handle<String> name) {
  if (IsOpen() && !isolate()->heap()->result_symbol()->Equals(*name)) {
    names_stack_.Add(Name(name, kVariableName));
  }
}
