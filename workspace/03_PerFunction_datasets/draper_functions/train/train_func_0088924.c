ComputeMonomorphicStub(
    LookupResult* lookup,
    State state,
    Code::ExtraICState extra_ic_state,
    Handle<Object> object,
    Handle<String> name) {
  int argc = target()->arguments_count();
  MaybeObject* maybe_code = NULL;
  switch (lookup->type()) {
    case FIELD: {
      int index = lookup->GetFieldIndex();
      maybe_code = isolate()->stub_cache()->ComputeCallField(argc,
                                                             kind_,
                                                             extra_ic_state,
                                                             *name,
                                                             *object,
                                                             lookup->holder(),
                                                             index);
      break;
    }
    case CONSTANT_FUNCTION: {


      JSFunction* function = lookup->GetConstantFunction();
      maybe_code =
          isolate()->stub_cache()->ComputeCallConstant(argc,
                                                       kind_,
                                                       extra_ic_state,
                                                       *name,
                                                       *object,
                                                       lookup->holder(),
                                                       function);
      break;
    }
    case NORMAL: {
      if (!object->IsJSObject()) return NULL;
      Handle<JSObject> receiver = Handle<JSObject>::cast(object);

      if (lookup->holder()->IsGlobalObject()) {
        GlobalObject* global = GlobalObject::cast(lookup->holder());
        JSGlobalPropertyCell* cell =
            JSGlobalPropertyCell::cast(global->GetPropertyCell(lookup));
        if (!cell->value()->IsJSFunction()) return NULL;
        JSFunction* function = JSFunction::cast(cell->value());
        maybe_code = isolate()->stub_cache()->ComputeCallGlobal(argc,
                                                                kind_,
                                                                extra_ic_state,
                                                                *name,
                                                                *receiver,
                                                                global,
                                                                cell,
                                                                function);
      } else {


        if (lookup->holder() != *receiver) return NULL;
        maybe_code = isolate()->stub_cache()->ComputeCallNormal(argc,
                                                                kind_,
                                                                extra_ic_state,
                                                                *name,
                                                                *receiver);
      }
      break;
    }
    case INTERCEPTOR: {
      ASSERT(HasInterceptorGetter(lookup->holder()));
      maybe_code = isolate()->stub_cache()->ComputeCallInterceptor(
          argc,
          kind_,
          extra_ic_state,
          *name,
          *object,
          lookup->holder());
      break;
    }
    default:
      maybe_code = NULL;
      break;
  }
  return maybe_code;
}
