setPref(int key, int value, bool transient) {
  JMPref* pref = new JMPref(key, value, transient, prefListHead);
  addPref(pref);
}
