print_call_path_to(callee_desc* target,
                                    int loop_id, int path_id, int caller_attr,
                                    callee_desc* prev)
{
  if (attr & (m_deadlock_free|m_visited)) {
    return path_id;
  }
  attr |= m_visited;
  if (prev != NULL) {
    for (overridden_method* ovr = overridden;
         ovr != NULL && path_id < max_shown_paths;
         ovr = ovr->next)
      {
        path_id = ovr->method->print_call_path_to(target, loop_id, path_id,
                                                  caller_attr, prev);
      }
  }
  for (callee_desc* callee = callees;
       callee != NULL && path_id < max_shown_paths;
       callee = callee->next)
    {
      int callee_attr = callee->attr & caller_attr;
      if (callee->method->attr & m_synchronized) {
        if (callee == target && !(callee_attr & callee_desc::i_self)) {
          print_call_sequence(prev, loop_id, ++path_id);
        }
      } else {
        callee->backtrace = prev;
        path_id = callee->method->print_call_path_to(target, loop_id,
                                                     path_id, callee_attr,
                                                     callee);
      }
    }
  attr &= ~m_visited;
  return path_id;
}
