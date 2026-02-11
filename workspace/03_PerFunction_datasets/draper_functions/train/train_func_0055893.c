setPref(int key, void* value, int len, bool transient) {
  JMPref* pref = new JMPref(key, value, len, transient, prefListHead);
  addPref(pref);
}
