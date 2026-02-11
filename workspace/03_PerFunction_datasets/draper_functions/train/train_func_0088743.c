find(const ArMapFileLine &groupParent) {
  for (iterator iter = begin(); iter != end(); iter++) {
    ArMapFileLineGroup &group = *iter;
    if ((group.getParentLine()->getLineNum() == groupParent.getLineNum()) &&
        true) {

        if (strcmp(group.getParentLine()->getLineText(),
                   groupParent.getLineText()) != 0) {
          ArLog::log(ArLog::Normal,
                     "Line #i text does not match:",
                     group.getParentLine()->getLineNum());
          ArLog::log(ArLog::Normal,
                      "\"%s\"",
                      group.getParentLine()->getLineText());
          ArLog::log(ArLog::Normal,
                      "\"%s\"",
                      groupParent.getLineText());

        }


                  ArLog::log(ArLog::Normal,
                              "Found #%i : %s",
                              groupParent.getLineNum(),
                              groupParent.getLineText());
      return iter;
    }
  }
  return end();
}
