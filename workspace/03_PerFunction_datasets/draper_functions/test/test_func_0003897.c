open_location_cb() {
  OpenLocationDialog dialog(_conf, _encodings);

  Document *doc = get_active();

  if (!doc) {
    dialog.disable_insert_to_active();
  }

  bool to_active = false;

  std::string error;
  if(dialog.run(error)) {
    if (doc) {
      to_active = dialog.insert_to_active();
    }

    int enc = dialog.get_encoding();
    std::string uri = dialog.get_uri();
    sigc::slot<void, bool, const std::string&> slot = sigc::bind(sigc::mem_fun(this, &MDI::signal_transfer_complete_cb), uri, enc, to_active);
    std::string error;
    if (!Network::add_transfer(uri, error, slot)) {
      katoob_error(error);
    }
  }
  else if (error.size() > 0) {
    katoob_error(error);
  }
}
