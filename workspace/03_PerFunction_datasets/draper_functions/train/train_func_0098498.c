SetBreakPoint(Handle<DebugInfo> debug_info,
                              int code_position,
                              int source_position,
                              int statement_position,
                              Handle<Object> break_point_object) {
  Isolate* isolate = Isolate::Current();
  Handle<Object> break_point_info(debug_info->GetBreakPointInfo(code_position));
  if (!break_point_info->IsUndefined()) {
    BreakPointInfo::SetBreakPoint(
        Handle<BreakPointInfo>::cast(break_point_info),
        break_point_object);
    return;
  }


  int index = kNoBreakPointInfo;
  for (int i = 0; i < debug_info->break_points()->length(); i++) {
    if (debug_info->break_points()->get(i)->IsUndefined()) {
      index = i;
      break;
    }
  }
  if (index == kNoBreakPointInfo) {

    Handle<FixedArray> old_break_points =
        Handle<FixedArray>(FixedArray::cast(debug_info->break_points()));
    Handle<FixedArray> new_break_points =
        isolate->factory()->NewFixedArray(
            old_break_points->length() +
            Debug::kEstimatedNofBreakPointsInFunction);

    debug_info->set_break_points(*new_break_points);
    for (int i = 0; i < old_break_points->length(); i++) {
      new_break_points->set(i, old_break_points->get(i));
    }
    index = old_break_points->length();
  }
  ASSERT(index != kNoBreakPointInfo);


  Handle<BreakPointInfo> new_break_point_info = Handle<BreakPointInfo>::cast(
      isolate->factory()->NewStruct(BREAK_POINT_INFO_TYPE));
  new_break_point_info->set_code_position(Smi::FromInt(code_position));
  new_break_point_info->set_source_position(Smi::FromInt(source_position));
  new_break_point_info->
      set_statement_position(Smi::FromInt(statement_position));
  new_break_point_info->set_break_point_objects(
      isolate->heap()->undefined_value());
  BreakPointInfo::SetBreakPoint(new_break_point_info, break_point_object);
  debug_info->break_points()->set(index, *new_break_point_info);
}
