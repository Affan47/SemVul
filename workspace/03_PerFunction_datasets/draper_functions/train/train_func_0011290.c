Initialize(Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(SecureContext::New);
  secure_context_constructor = Persistent<FunctionTemplate>::New(t);

  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(String::NewSymbol("SecureContext"));

  NODE_SET_PROTOTYPE_METHOD(t, "init", SecureContext::Init);
  NODE_SET_PROTOTYPE_METHOD(t, "setKey", SecureContext::SetKey);
  NODE_SET_PROTOTYPE_METHOD(t, "setCert", SecureContext::SetCert);
  NODE_SET_PROTOTYPE_METHOD(t, "addCACert", SecureContext::AddCACert);
  NODE_SET_PROTOTYPE_METHOD(t, "addCRL", SecureContext::AddCRL);
  NODE_SET_PROTOTYPE_METHOD(t, "addRootCerts", SecureContext::AddRootCerts);
  NODE_SET_PROTOTYPE_METHOD(t, "setCiphers", SecureContext::SetCiphers);
  NODE_SET_PROTOTYPE_METHOD(t, "setOptions", SecureContext::SetOptions);
  NODE_SET_PROTOTYPE_METHOD(t, "setSessionIdContext",
                               SecureContext::SetSessionIdContext);
  NODE_SET_PROTOTYPE_METHOD(t, "close", SecureContext::Close);

  target->Set(String::NewSymbol("SecureContext"), t->GetFunction());
}
