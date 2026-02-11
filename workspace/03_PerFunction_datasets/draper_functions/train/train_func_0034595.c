pop_command() {
    stack.pop_back();
    if (stack.empty())
      push_command(Parm);
  }
