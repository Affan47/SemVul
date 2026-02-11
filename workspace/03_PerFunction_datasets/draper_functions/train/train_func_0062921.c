toggle_bell_level(haywire_state *app) {
  switch(app->bell_level) {
    case E_PARSE:
    app->bell_level = E_NOTICE; break;
    case E_NOTICE:
    app->bell_level = E_MISSING_FILE; break;
    case E_MISSING_FILE:
    app->bell_level = E_PARSE; break;
  }
}
