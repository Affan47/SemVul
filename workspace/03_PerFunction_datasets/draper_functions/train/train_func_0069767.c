execute_cb() {
  Document *doc = get_active();
  if (!doc) {
    return;
  }

  ExecDialog dlg(_conf);

  if (dlg.run()) {
    bool new_buffer = dlg.get_new_buffer();
    std::string command = dlg.get_command();
    _conf.exec_cmd_prepend(command);

    unsigned found = 0;
    for (unsigned x = 0; x < command.size(); x++) {

      if ((command[x] == '%') && (command[x+1] == 's')) {
	++found;
      }
    }

    if (found > 1) {
      katoob_error(_("You can use only one '%s'"));
      return;
    }

    std::string error;
    std::string cmd;
    std::string text;
    TempFile tf;
    if (found == 1) {
      if (!tf.ok(error)) {
	katoob_error(error);
	return;
      }


      text = doc->get_text();
      if (!tf.write(text, error)) {
	katoob_error(error);
	return;
      }
      text.clear();
      cmd = Utils::substitute(command, tf.get_name());
    }
    else {
      cmd = command;
    }

    if (!Pipe::exec(command, cmd, text, error)) {
      katoob_error(error);
      return;
    }

    if(!new_buffer) {
      doc->set_text(text);
    }
    else {

      Document *d = create_document();
      if (d) {
	d->set_text(text);
      }
    }
  }
}
