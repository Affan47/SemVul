Initialize(Handle<Object> target) {
  HandleWrap::Initialize(target);

  HandleScope scope;

  udp_slab_sym = Persistent<String>::New(String::NewSymbol("udpslab"));
  buffer_sym = NODE_PSYMBOL("buffer");
  port_symbol = NODE_PSYMBOL("port");
  address_symbol = NODE_PSYMBOL("address");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(String::NewSymbol("UDP"));

  NODE_SET_PROTOTYPE_METHOD(t, "bind", Bind);
  NODE_SET_PROTOTYPE_METHOD(t, "send", Send);
  NODE_SET_PROTOTYPE_METHOD(t, "bind6", Bind6);
  NODE_SET_PROTOTYPE_METHOD(t, "send6", Send6);
  NODE_SET_PROTOTYPE_METHOD(t, "close", Close);
  NODE_SET_PROTOTYPE_METHOD(t, "recvStart", RecvStart);
  NODE_SET_PROTOTYPE_METHOD(t, "recvStop", RecvStop);
  NODE_SET_PROTOTYPE_METHOD(t, "getsockname", GetSockName);

  target->Set(String::NewSymbol("UDP"),
              Persistent<FunctionTemplate>::New(t)->GetFunction());
}
