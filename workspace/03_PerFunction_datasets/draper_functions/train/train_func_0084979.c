fxdbus_addwatch(DBusWatch *watch,void * data) {
  FXTRACE((35,"fxdbus_addwatch()\n"));
  GMDBus * dc = reinterpret_cast<GMDBus*>(data);
  FXuint mode  = INPUT_EXCEPT;
  FXuint flags = dbus_watch_get_flags(watch);


  if (!dbus_watch_get_enabled(watch)) return true;

  if (flags&DBUS_WATCH_READABLE)
      mode|=INPUT_READ;
  if (flags&DBUS_WATCH_WRITABLE)
      mode|=INPUT_WRITE;

#if DBUSVERSION == MKDBUSVERSION(1,1,20) || DBUSVERSION >= MKDBUSVERSION(1,2,0)
#if FOXVERSION < FXVERSION(1,7,0)
  fxdbus.insert(dbus_watch_get_unix_fd(watch),watch);
  return FXApp::instance()->addInput((FXInputHandle)dbus_watch_get_unix_fd(watch),mode,dc,GMDBus::ID_HANDLE);
#else
  return FXApp::instance()->addInput(dc,GMDBus::ID_HANDLE,(FXInputHandle)dbus_watch_get_unix_fd(watch),mode,watch);
#endif
#else
#if FOXVERSION < FXVERSION(1,7,0)
  fxdbus.insert(dbus_watch_get_fd(watch),watch);
  return FXApp::instance()->addInput((FXInputHandle)dbus_watch_get_fd(watch),mode,dc,GMDBus::ID_HANDLE);
#else
  return FXApp::instance()->addInput(dc,GMDBus::ID_HANDLE,(FXInputHandle)dbus_watch_get_fd(watch),mode,watch);
#endif
#endif

  }
