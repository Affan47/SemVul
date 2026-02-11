GetScriptName(int index) {
    if (index == 0) return Vector<const char>("native proxy.js", 15);
    if (index == 1) return Vector<const char>("native weakmap.js", 17);
    return Vector<const char>("", 0);
  }
