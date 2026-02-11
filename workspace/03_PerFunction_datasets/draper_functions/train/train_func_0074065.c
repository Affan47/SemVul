DateTimeConfigurationChangeNotification() {
  i::Isolate* isolate = i::Isolate::Current();
  ON_BAILOUT(isolate, "v8::Date::DateTimeConfigurationChangeNotification()",
             return);
  LOG_API(isolate, "Date::DateTimeConfigurationChangeNotification");
  ENTER_V8(isolate);

  i::HandleScope scope(isolate);

  i::Handle<i::String> func_name_str =
      isolate->factory()->LookupAsciiSymbol("ResetDateCache");
  i::MaybeObject* result =
      isolate->js_builtins_object()->GetProperty(*func_name_str);
  i::Object* object_func;
  if (!result->ToObject(&object_func)) {
    return;
  }

  if (object_func->IsJSFunction()) {
    i::Handle<i::JSFunction> func =
        i::Handle<i::JSFunction>(i::JSFunction::cast(object_func));


    bool caught_exception = false;
    i::Execution::TryCall(func,
                          isolate->js_builtins_object(),
                          0,
                          NULL,
                          &caught_exception);
  }
}
