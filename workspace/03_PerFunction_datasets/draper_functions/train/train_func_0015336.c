AllocateJSObject(JSFunction* constructor,
                                    PretenureFlag pretenure) {

  if (!constructor->has_initial_map()) {
    Object* initial_map;
    { MaybeObject* maybe_initial_map = AllocateInitialMap(constructor);
      if (!maybe_initial_map->ToObject(&initial_map)) return maybe_initial_map;
    }
    constructor->set_initial_map(Map::cast(initial_map));
    Map::cast(initial_map)->set_constructor(constructor);
  }

  MaybeObject* result =
      AllocateJSObjectFromMap(constructor->initial_map(), pretenure);
#ifdef DEBUG

  Object* non_failure;
  ASSERT(!result->ToObject(&non_failure) || !non_failure->IsGlobalObject());
#endif
  return result;
}
