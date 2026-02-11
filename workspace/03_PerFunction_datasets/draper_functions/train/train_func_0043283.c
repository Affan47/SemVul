SetBreakPoint(Handle<SharedFunctionInfo> shared,
                          Handle<Object> break_point_object,
                          int* source_position) {
  HandleScope scope;

  if (!EnsureDebugInfo(shared)) {

    return;
  }

  Handle<DebugInfo> debug_info = GetDebugInfo(shared);

  ASSERT(source_position >= 0);


  BreakLocationIterator it(debug_info, SOURCE_BREAK_LOCATIONS);
  it.FindBreakLocationFromPosition(*source_position);
  it.SetBreakPoint(break_point_object);

  *source_position = it.position();


  ASSERT(debug_info->GetBreakPointCount() > 0);
}
