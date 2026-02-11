CreateEnvironment(
    Isolate* isolate,
    Handle<Object> global_object,
    v8::Handle<v8::ObjectTemplate> global_template,
    v8::ExtensionConfiguration* extensions) {
  HandleScope scope;
  Handle<Context> env;
  Genesis genesis(isolate, global_object, global_template, extensions);
  env = genesis.result();
  if (!env.is_null()) {
    if (InstallExtensions(env, extensions)) {
      return env;
    }
  }
  return Handle<Context>();
}
