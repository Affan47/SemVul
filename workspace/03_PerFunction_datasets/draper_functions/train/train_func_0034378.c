AddScriptToScriptCache(Handle<Script> script) {
  if (script_cache_ != NULL) {
    script_cache_->Add(script);
  }
}
