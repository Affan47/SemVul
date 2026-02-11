getFlagMap(string match) {

  match = toLower(match);
  map<string, Flag> flagMap;

  for (map<string,Flag>::iterator flagEntry = flags.begin();
       flagEntry != flags.end(); ++flagEntry)
    if (flagEntry->first.find(match) != string::npos)
      flagMap[flagEntry->first] = flagEntry->second;
  return flagMap;
}
