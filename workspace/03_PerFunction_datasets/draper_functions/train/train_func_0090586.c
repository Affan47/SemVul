do_it(CS& cmd, CARD_LIST* Scope)
  {
    PARAM_LIST* pl = Scope->params();
    if (cmd.is_end()) {
      pl->print(IO::mstdout, OPT::language);
      IO::mstdout << '\n';
    }else{
      pl->parse(cmd);
    }
  }
}
