EnsureDebugInfo(Handle<SharedFunctionInfo> shared) {

  if (HasDebugInfo(shared)) return true;


  if (!EnsureCompiled(shared, CLEAR_EXCEPTION)) return false;


  if (!has_break_points_) {
    Deoptimizer::DeoptimizeAll();
  }


  Handle<DebugInfo> debug_info = Factory::NewDebugInfo(shared);


  DebugInfoListNode* node = new DebugInfoListNode(*debug_info);
  node->set_next(debug_info_list_);
  debug_info_list_ = node;


  has_break_points_ = true;

  return true;
}
