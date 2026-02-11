attached_chains_output(AUDIO_IO* aiod) const
{

  DBC_REQUIRE(is_selected() == true);


  vector<string> t = selected_chainsetup_repp->get_attached_chains_to_output(aiod);
  string out = "";
  vector<string>::const_iterator p = t.begin();
  while(p != t.end()) {
    out += *p;
    ++p;
    if (p != t.end()) out += ",";
  }
  return out;
}
