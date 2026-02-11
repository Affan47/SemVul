Initialize(Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(ChildProcess::New);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(String::NewSymbol("ChildProcess"));

  pid_symbol = NODE_PSYMBOL("pid");
  onexit_symbol = NODE_PSYMBOL("onexit");

  NODE_SET_PROTOTYPE_METHOD(t, "spawn", ChildProcess::Spawn);
  NODE_SET_PROTOTYPE_METHOD(t, "kill", ChildProcess::Kill);

  target->Set(String::NewSymbol("ChildProcess"), t->GetFunction());
}
