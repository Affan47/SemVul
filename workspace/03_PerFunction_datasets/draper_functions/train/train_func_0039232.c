add_list(CS& cmd)
{
  int oldcount = size();
  std::string what(cmd.ctos(TOKENTERM));
  if (what.empty()) {untested();
    cmd.warn(bWARNING, "need a probe");
  }else{
  }

  int paren = cmd.skip1b('(');
  if (cmd.umatch("nodes ")) {

    add_all_nodes(what);
  }else if (cmd.umatch("0")) {

    push_new_probe(what, 0);
  }else if (cmd.is_alnum() || cmd.match1("*?")) {

    unsigned here1 = cmd.cursor();
    bool found_something = add_branches(cmd.ctos(),what,&CARD_LIST::card_list);
    if (!found_something) {
      cmd.warn(bWARNING, here1, "no match");
    }else{
    }
    for (;;) {

      if (!(cmd.is_alnum() || cmd.match1("*?"))) {
	break;
      }else{
      }
      unsigned here2 = cmd.cursor();
      found_something = add_branches(cmd.ctos(),what,&CARD_LIST::card_list);
      if (!found_something) {itested();
	cmd.reset(here2);
	break;
      }else{
      }
    }
  }else{itested();
    cmd.warn(bDANGER, "need device or node");
  }
  paren -= cmd.skip1b(')');
  if (paren != 0) {itested();
    cmd.warn(bWARNING, "need )");
  }else{
  }

  if (cmd.skip1b('(')) {
    double lo = cmd.ctof();
    double hi = cmd.ctof();
    for (iterator p = begin() + oldcount;  p != end();  ++p) {
      p->set_limit(lo,hi);
    }
    if (!cmd.skip1b(')')) {untested();
      cmd.check(bWARNING, "need )");
    }else{
    }
  }else{
  }
}
