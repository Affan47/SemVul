parse_command(CS& cmd, DEV_DOT* x)
{
  assert(x);
  x->set(cmd.fullstring());
  CARD_LIST* scope = (x->owner()) ? x->owner()->subckt() : &CARD_LIST::card_list;

  cmd.reset().skipbl();
  if ((cmd >> "model |simulator |parameters |subckt ")) {
    cmd.reset();
    CMD::cmdproc(cmd, scope);
  }else{
    std::string label;
    cmd >> label;

    if (label != "-") {
      unsigned here = cmd.cursor();
      std::string command;
      cmd >> command;
      cmd.reset(here);
      std::string file_name = label + '.' + command;
      std::string s = cmd.tail() + " > " + file_name;
      CS augmented_cmd(CS::_STRING, s);
      CMD::cmdproc(augmented_cmd, scope);
    }else{
      CMD::cmdproc(cmd, scope);
    }
  }
  delete x;
  return NULL;
}
