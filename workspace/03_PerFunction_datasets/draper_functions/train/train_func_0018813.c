fxdbus_addtimeout(DBusTimeout *timeout,void *) {

  GMDBusTimeout * tm = fxdbus.find(timeout);
  if (tm==NULL)
    tm = new GMDBusTimeout(timeout);

  tm->add();
  return true;
  }
