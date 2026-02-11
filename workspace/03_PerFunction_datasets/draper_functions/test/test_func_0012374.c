rescan_makeSubst(list<ServerLine>& entries,
    Map::iterator mapl, const ServerLine& l, bool& printError) {

  vector<string> words;
  ConfigFile::split(words, *l.line, l.valueStart);
# if 0
  if (words.size() > 1 && printError) {


    string err = subst(_("Line contains more than one URI, ignoring part "
                         "after `%1' (maybe you need to use \"\" quotes?)"),
                       words[0]);
    size_t lineNr = 1;
    ConfigFile::iterator findLineNr = l.line;
    while (findLineNr != config->begin()) { ++lineNr; --findLineNr; }
    freporter.error(err, lineNr);
    printError = false;
  }
# endif


  vector<string>& uris = mapl->second;


  if (words.empty()) {

    uris.push_back("");
    return;
  }

  string& s = words.front();
  string::size_type colon = s.find(':');
  if (colon == string::npos) {
    debug("Appending to entry for `%1' fixed mapping `%2'", mapl->first, s);
    uris.push_back(s);
    return;
  }


  string refLabel(s, 0, colon);
  debug("rescan_addLabel   ref `%1'", refLabel);


  Map::iterator mapr = rescan_addLabel(entries, refLabel, printError);
  Paranoid(mapr != serverMap.end());
  if (mapr->second.empty()) {
    debug("Appending to entry for `%1' fixed mapping `%2'", mapl->first, s);
    uris.push_back(s);
    return;
  }


  debug("Appending to entry for `%1' mappings for `%2':",
        mapl->first, refLabel);
  for (vector<string>::iterator i = mapr->second.begin(),
         e = mapr->second.end(); i != e; ++i) {
    uris.push_back(*i);
    uris.back().append(s, colon + 1, string::npos);
    debug("    %1", uris.back());
  }
  return;
}
