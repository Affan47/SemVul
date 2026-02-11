PatchFunctionPositions(Handle<JSArray> shared_info_array,
                                      Handle<JSArray> position_change_array) {
  SharedInfoWrapper shared_info_wrapper(shared_info_array);
  Handle<SharedFunctionInfo> info = shared_info_wrapper.GetInfo();

  info->set_start_position(TranslatePosition(info->start_position(),
                                             position_change_array));
  info->set_end_position(TranslatePosition(info->end_position(),
                                           position_change_array));

  info->set_function_token_position(
      TranslatePosition(info->function_token_position(),
      position_change_array));


  Handle<Code> patched_code = PatchPositionsInCode(Handle<Code>(info->code()),
                                                   position_change_array);
  if (*patched_code != info->code()) {


    ReplaceCodeObject(info->code(), *patched_code);
  }

  if (info->debug_info()->IsDebugInfo()) {
    Handle<DebugInfo> debug_info(DebugInfo::cast(info->debug_info()));
    Handle<Code> patched_orig_code =
        PatchPositionsInCode(Handle<Code>(debug_info->original_code()),
                             position_change_array);
    if (*patched_orig_code != debug_info->original_code()) {


      debug_info->set_original_code(*patched_orig_code);
    }

    Handle<FixedArray> break_point_infos(debug_info->break_points());
    for (int i = 0; i < break_point_infos->length(); i++) {
      if (!break_point_infos->get(i)->IsBreakPointInfo()) {
        continue;
      }
      Handle<BreakPointInfo> info(
          BreakPointInfo::cast(break_point_infos->get(i)));
      int new_position = TranslatePosition(info->source_position()->value(),
          position_change_array);
      info->set_source_position(Smi::FromInt(new_position));
    }
  }

}
