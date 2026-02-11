New(
      v8::Handle<FunctionTemplate> constructor) {
  if (IsDeadCheck("v8::ObjectTemplate::New()")) return Local<ObjectTemplate>();
  EnsureInitialized("v8::ObjectTemplate::New()");
  LOG_API("ObjectTemplate::New");
  ENTER_V8;
  i::Handle<i::Struct> struct_obj =
      i::Factory::NewStruct(i::OBJECT_TEMPLATE_INFO_TYPE);
  i::Handle<i::ObjectTemplateInfo> obj =
      i::Handle<i::ObjectTemplateInfo>::cast(struct_obj);
  InitializeTemplate(obj, Consts::OBJECT_TEMPLATE);
  if (!constructor.IsEmpty())
    obj->set_constructor(*Utils::OpenHandle(*constructor));
  obj->set_internal_field_count(i::Smi::FromInt(0));
  return Utils::ToLocal(obj);
}
