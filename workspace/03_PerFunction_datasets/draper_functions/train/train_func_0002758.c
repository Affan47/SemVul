edlauncher(const char* name) {
  if (_edlauncherlist) {
    AttributeValue* av = _edlauncherlist->find(name);
    return av ? (editor_launcher) av->obj_val() : nil;
  } else
    return nil;
}
