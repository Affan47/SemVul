ToBooleanTypes(unsigned ast_id) {
  Handle<Object> object = GetInfo(ast_id);
  return object->IsCode() ? Handle<Code>::cast(object)->to_boolean_state() : 0;
}
