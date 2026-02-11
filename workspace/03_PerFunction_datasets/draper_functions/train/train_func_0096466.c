ToObject(Context* global_context) {
  if (IsNumber()) {
    return CreateJSValue(global_context->number_function(), this);
  } else if (IsBoolean()) {
    return CreateJSValue(global_context->boolean_function(), this);
  } else if (IsString()) {
    return CreateJSValue(global_context->string_function(), this);
  }
  ASSERT(IsJSObject());
  return this;
}
