plugin(const char *name) {
  char buf[34];
  Fl_Plugin *ret = 0;
  if (groupExists(name)) {
    Fl_Preferences pin(this, name);
    pin.get("address", buf, "", 34);
    if (buf[0]=='@') ret = (Fl_Plugin*)a2p(buf+1);
#ifdef FL_PLUGIN_VERBOSE
    printf("Fl_Plugin: returning plugin named \"%s\": (%s) %p\n", name, buf, ret);
#endif
    return ret;
  } else {
#ifdef FL_PLUGIN_VERBOSE
    printf("Fl_Plugin: no plugin found named \"%s\"\n", name);
#endif
    return 0L;
  }
}
