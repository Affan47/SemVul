New(const Arguments& args) {
  if (!args.IsConstructCall()) {
    return FromConstructorTemplate(constructor_template, args);
  }

  HandleScope scope;

  if (args.Length() != 1 || !args[0]->IsInt32()) {
    return ThrowException(String::New("Bad arguments"));
  }

  int sig = args[0]->Int32Value();

  SignalWatcher *w = new SignalWatcher(sig);
  w->Wrap(args.Holder());

  return args.This();
}
