AllocateJSFunctionProxy(Object* handler,
                                           Object* call_trap,
                                           Object* construct_trap,
                                           Object* prototype) {


  Map* map;
  MaybeObject* maybe_map_obj =
      AllocateMap(JS_FUNCTION_PROXY_TYPE, JSFunctionProxy::kSize);
  if (!maybe_map_obj->To<Map>(&map)) return maybe_map_obj;
  map->set_prototype(prototype);


  JSFunctionProxy* result;
  MaybeObject* maybe_result = Allocate(map, NEW_SPACE);
  if (!maybe_result->To<JSFunctionProxy>(&result)) return maybe_result;
  result->InitializeBody(map->instance_size(), Smi::FromInt(0));
  result->set_handler(handler);
  result->set_call_trap(call_trap);
  result->set_construct_trap(construct_trap);
  return result;
}
