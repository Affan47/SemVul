UpdateCaches(LookupResult* lookup,
                                State state,
                                Handle<JSObject> receiver,
                                Handle<String> name,
                                Handle<Object> value) {

  if (receiver->IsJSGlobalProxy()) return;


  if (!lookup->IsPropertyOrTransition() || !lookup->IsCacheable()) return;


  if (lookup->IsReadOnly()) return;


  PropertyType type = lookup->type();


  Object* code = NULL;

  switch (type) {
    case FIELD: {
      code = StubCache::ComputeKeyedStoreField(*name, *receiver,
                                               lookup->GetFieldIndex());
      break;
    }
    case MAP_TRANSITION: {
      if (lookup->GetAttributes() == NONE) {
        HandleScope scope;
        ASSERT(type == MAP_TRANSITION);
        Handle<Map> transition(lookup->GetTransitionMap());
        int index = transition->PropertyIndexFor(*name);
        code = StubCache::ComputeKeyedStoreField(*name, *receiver,
                                                 index, *transition);
        break;
      }

    }
    default: {


      code = generic_stub();
      break;
    }
  }


  if (code == NULL || code->IsFailure()) return;


  ASSERT(state != MONOMORPHIC_PROTOTYPE_FAILURE);
  if (state == UNINITIALIZED || state == PREMONOMORPHIC) {
    set_target(Code::cast(code));
  } else if (state == MONOMORPHIC) {
    set_target(megamorphic_stub());
  }

#ifdef DEBUG
  TraceIC("KeyedStoreIC", name, state, target());
#endif
}
