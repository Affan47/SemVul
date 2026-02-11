Initialize(Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(IOWatcher::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("IOWatcher"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "start", IOWatcher::Start);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "stop", IOWatcher::Stop);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "set", IOWatcher::Set);

  target->Set(String::NewSymbol("IOWatcher"), constructor_template->GetFunction());

  callback_symbol = NODE_PSYMBOL("callback");
}
