ScriptGetLineEnds(Object* object, void*) {
  HandleScope scope;
  Handle<Script> script(Script::cast(JSValue::cast(object)->value()));
  InitScriptLineEnds(script);
  ASSERT(script->line_ends()->IsFixedArray());
  Handle<FixedArray> line_ends(FixedArray::cast(script->line_ends()));

  ASSERT(*line_ends == Heap::empty_fixed_array() ||
         line_ends->map() == Heap::fixed_cow_array_map());
  Handle<JSArray> js_array = Factory::NewJSArrayWithElements(line_ends);
  return *js_array;
}
