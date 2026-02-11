xsettings_client_new_with_grab_funcs (Display             *display,
		                      int                  screen,
		                      XSettingsNotifyFunc  notify,
		                      XSettingsWatchFunc   watch,
		                      void                *cb_data,
		                      XSettingsGrabFunc    grab,
		                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  char buffer[256];
  char *atom_names[3];
  Atom atoms[3];

  client = malloc (sizeof *client);
  if (!client)
    return NULL;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = NULL;

  sprintf(buffer, "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#else
  atoms[0] = XInternAtom (display, atom_names[0], False);
  atoms[1] = XInternAtom (display, atom_names[1], False);
  atoms[2] = XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];


  add_events (display, RootWindow (display, screen), StructureNotifyMask);

  if (client->watch)
    client->watch (RootWindow (display, screen), True, StructureNotifyMask,
		   client->cb_data);

  check_manager_window (client);

  return client;
}
