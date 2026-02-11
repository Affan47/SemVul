Get(CS& cmd, const std::string& key, LANGUAGE** val)
{
  if (cmd.umatch(key + " {=}")) {
    LANGUAGE* lang = language_dispatcher[cmd];
    if (lang) {
      *val = lang;
    }else{
    }
    return true;
  }else{
    return false;
  }
}
