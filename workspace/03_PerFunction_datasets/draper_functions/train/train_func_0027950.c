SetData(v8::Handle<String> data) {
  ON_BAILOUT("v8::Script::SetData()", return);
  LOG_API("Script::SetData");
  {
    HandleScope scope;
    i::Handle<i::SharedFunctionInfo> function_info = OpenScript(this);
    i::Handle<i::Object> raw_data = Utils::OpenHandle(*data);
    i::Handle<i::Script> script(i::Script::cast(function_info->script()));
    script->set_data(*raw_data);
  }
}
