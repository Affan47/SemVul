writeLValueExpr(pair< pair<int, bool>, string>& lv) {
  stringstream s;

  s << "lea edx, [" << X86::makeID(lv.second) << "]";
  writeTEXT(s.str());
  writeTEXT("lea edx, [edx + ecx * SIZEOF_DWORD]");

  if(lv.first.second) {

    writeTEXT("push edx");
  } else {
    writeTEXT("push dword [edx]");
  }
}
