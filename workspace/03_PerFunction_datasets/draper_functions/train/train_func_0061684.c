audio_real_init(const char *const spec_name,
		     const char *const prefered_plugin_name)
{
  const char *filename;
  const char *file_capstr;
  char us_capstr[] = "+soundspec";

  if (strcmp(prefered_plugin_name, "none") == 0) {

    log_verbose("Proceeding with sound support disabled.");
    tagfile = NULL;
    return;
  }
  if (num_plugins_used == 1) {

    log_normal(_("No real audio plugin present."));
    log_normal(_("Proceeding with sound support disabled."));
    log_normal(_("For sound support, install SDL_mixer"));
    log_normal("http://www.libsdl.org/projects/SDL_mixer/index.html");
    tagfile = NULL;
    return;
  }
  if (!spec_name) {
    log_fatal("No sound spec-file given!");
    exit(EXIT_FAILURE);
  }
  log_verbose("Initializing sound using %s...", spec_name);
  filename = soundspec_fullname(spec_name);
  if (!filename) {
    log_error("Cannot find sound spec-file \"%s\".", spec_name);
    log_normal(_("To get sound you need to download a sound set!"));
    log_normal(_("Get sound sets from <%s>."),
               "http://www.freeciv.org/wiki/Sounds");
    log_normal(_("Proceeding with sound support disabled."));
    tagfile = NULL;
    return;
  }
  if (!(tagfile = secfile_load(filename, TRUE))) {
    log_fatal(_("Could not load sound spec-file '%s':\n%s"), filename,
              secfile_error());
    exit(EXIT_FAILURE);
  }

  file_capstr = secfile_lookup_str(tagfile, "soundspec.options");
  if (NULL == file_capstr) {
    log_fatal("Audio spec-file \"%s\" doesn't have capability string.",
              filename);
    exit(EXIT_FAILURE);
  }
  if (!has_capabilities(us_capstr, file_capstr)) {
    log_fatal("sound spec-file appears incompatible:");
    log_fatal("  file: \"%s\"", filename);
    log_fatal("  file options: %s", file_capstr);
    log_fatal("  supported options: %s", us_capstr);
    exit(EXIT_FAILURE);
  }
  if (!has_capabilities(file_capstr, us_capstr)) {
    log_fatal("sound spec-file claims required option(s) "
              "which we don't support:");
    log_fatal("  file: \"%s\"", filename);
    log_fatal("  file options: %s", file_capstr);
    log_fatal("  supported options: %s", us_capstr);
    exit(EXIT_FAILURE);
  }

  free((void *) filename);

  atexit(audio_shutdown);

  if (prefered_plugin_name[0] != '\0') {
    if (!audio_select_plugin(prefered_plugin_name))
      log_normal(_("Proceeding with sound support disabled."));
    return;
  }

#ifdef AUDIO_SDL
  if (audio_select_plugin("sdl")) return;
#endif
  log_normal(_("No real audio subsystem managed to initialize!"));
  log_normal(_("Perhaps there is some misconfiguration or bad permissions."));
  log_normal(_("Proceeding with sound support disabled."));
}
