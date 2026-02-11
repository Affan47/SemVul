Tick(void) {

  if (!need_tick_cb) return;

  need_tick_cb = false;
  ev_idle_stop(EV_DEFAULT_UC_ &tick_spinner);

  HandleScope scope;

  if (tick_callback_sym.IsEmpty()) {

    tick_callback_sym =
      Persistent<String>::New(String::NewSymbol("_tickCallback"));
  }

  Local<Value> cb_v = process->Get(tick_callback_sym);
  if (!cb_v->IsFunction()) return;
  Local<Function> cb = Local<Function>::Cast(cb_v);

  TryCatch try_catch;

  cb->Call(process, 0, NULL);

  if (try_catch.HasCaught()) {
    FatalException(try_catch);
  }
}
