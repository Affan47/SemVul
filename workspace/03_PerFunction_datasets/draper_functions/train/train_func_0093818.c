GenerateMissBranch() {
  MaybeObject* maybe_obj =
      isolate()->stub_cache()->ComputeCallMiss(arguments().immediate(),
                                               kind_,
                                               extra_ic_state_);
  Object* obj;
  if (!maybe_obj->ToObject(&obj)) return maybe_obj;
  __ Jump(Handle<Code>(Code::cast(obj)), RelocInfo::CODE_TARGET);
  return obj;
}
