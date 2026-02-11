ghosd_main_iterations(Ghosd *ghosd) {
  while (XPending(ghosd->dpy))
    ghosd_main_iteration(ghosd);
}
