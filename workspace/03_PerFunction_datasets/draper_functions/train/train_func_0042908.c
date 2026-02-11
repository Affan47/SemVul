New(const Arguments& args) {
  if (!args.IsConstructCall()) {
    return FromConstructorTemplate(constructor_template, args);
  }

  HandleScope scope;

  struct ares_options options;
  int optmask = 0;

  Channel *c = new Channel();
  c->Wrap(args.This());

  if (args.Length() > 0) {
    if(!args[0]->IsObject()) {
      return ThrowException(Exception::TypeError(
            String::New("Bad Options Argument")));
    }

    Local<Object> options_o = Local<Object>::Cast(args[0]);

    Local<Value> cb = options_o->Get(String::NewSymbol("SOCK_STATE_CB"));
    if (!cb.IsEmpty()) {
      c->handle_->Set(callback_symbol, cb);
      options.sock_state_cb_data = c;
      options.sock_state_cb = Channel::SockStateCb;
      optmask |= ARES_OPT_SOCK_STATE_CB;
    }
  }

  ares_init_options(&c->channel, &options, optmask);

  return args.This();
}
