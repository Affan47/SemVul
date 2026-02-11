unplug_wrappers(httrackp * opt) {
  if (opt->libHandles.handles != NULL) {
    int i;

    for(i = 0; i < opt->libHandles.count; i++) {
      if (opt->libHandles.handles[i].handle != NULL) {

        t_hts_unplug unplug =
          (t_hts_unplug) getFunctionPtr(opt->libHandles.handles[i].handle,
                                        "hts_unplug");
        if (unplug != NULL)
          unplug(opt);
        closeFunctionLib(opt->libHandles.handles[i].handle);
        opt->libHandles.handles[i].handle = NULL;
      }
      if (opt->libHandles.handles[i].moduleName != NULL) {
        freet(opt->libHandles.handles[i].moduleName);
        opt->libHandles.handles[i].moduleName = NULL;
      }
    }
    freet(opt->libHandles.handles);
    opt->libHandles.handles = NULL;
    opt->libHandles.count = 0;
  }
}
