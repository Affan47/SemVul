SetBreakPoint(Handle<SharedFunctionInfo> shared,
                          int source_position,
                          Handle<Object> break_point_object) {
  HandleScope scope;

  if (!EnsureDebugInfo(shared)) {

    return;
  }

  Handle<DebugInfo> debug_info = GetDebugInfo(shared);

  ASSERT(source_position >= 0);


  BreakLocationIterator it(debug_info, SOURCE_BREAK_LOCATIONS);
  it.FindBreakLocationFromPosition(source_position);
  it.SetBreakPoint(break_point_object);


  ASSERT(debug_info->GetBreakPointCount() > 0);
}
