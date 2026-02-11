add_to_concurrent_closure(callee_desc* caller,
                                            int caller_attr, int depth)
{
  for (overridden_method* ovr=overridden; ovr != NULL; ovr=ovr->next) {
    add_to_concurrent_closure(caller, caller_attr, depth);
  }
  if (attr & m_synchronized) {
    if ((caller_attr & (callee_desc::i_synchronized|callee_desc::i_self))
        == callee_desc::i_synchronized && (attr & m_wait))
      {
        int callee_attr = callee_desc::i_self|callee_desc::i_wait_deadlock;
        callee_desc* up = caller;
        while (true) {
          callee_attr &= up->attr;
          if (up->backtrace == NULL
              || (!(callee_attr & callee_desc::i_self) &&
                  ((up->attr & callee_desc::i_synchronized)
                   || (((callee_desc*)up->backtrace)->method->attr
                       & m_synchronized))))
            {
              break;
            }
          up = (callee_desc*)up->backtrace;
        }

        if (!(callee_attr & callee_desc::i_wait_deadlock)) {
          message_at(msg_wait, cls->source_file, wait_line, this);
          callee_desc* bt = caller;
          while (true) {
            bt->message(msg_wait_path, bt->method);
            bt->attr |= callee_desc::i_wait_deadlock;
            if (bt == up) break;
            bt = (callee_desc*)bt->backtrace;
          }
        }
      }
    attr |= m_concurrent;
    if ((caller_attr & (callee_desc::i_synchronized|callee_desc::i_self))
        == callee_desc::i_synchronized && !(attr & m_visited))
      {
        attr |= m_visited;
        for (callee_desc* callee = callees;
             callee != NULL;
             callee = callee->next)
          {
            if (callee->attr & callee_desc::i_self) {
              callee->backtrace = caller;
              callee->method->add_to_concurrent_closure
                (callee, callee_desc::i_synchronized, 0);
            }
          }
        attr &= ~m_visited;
      }
  }
  else if (!(attr & m_visited)
           && !((depth != 0 || (caller_attr & callee_desc::i_self))
                && (attr & m_concurrent)))
    {
      if (attr & m_concurrent) {
        depth += 1;
      }
      attr |= m_visited|m_concurrent;
      for (callee_desc* callee=callees; callee != NULL; callee=callee->next){
        int callee_attr = caller_attr;
        if (callee->attr & callee_desc::i_synchronized) {
          callee_attr = callee_desc::i_synchronized;
        } else {
          callee_attr &= callee->attr|~callee_desc::i_self;
        }
        callee->backtrace = caller;
        callee->method->add_to_concurrent_closure(callee, callee_attr,
                                                  depth);
      }
      attr &= ~m_visited;
    }
}
