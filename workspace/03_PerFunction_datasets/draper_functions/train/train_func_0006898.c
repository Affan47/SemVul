ClearBreakPoint(Handle<DebugInfo> debug_info,
                                int code_position,
                                Handle<Object> break_point_object) {
  Handle<Object> break_point_info(debug_info->GetBreakPointInfo(code_position));
  if (break_point_info->IsUndefined()) return;
  BreakPointInfo::ClearBreakPoint(
      Handle<BreakPointInfo>::cast(break_point_info),
      break_point_object);
}
