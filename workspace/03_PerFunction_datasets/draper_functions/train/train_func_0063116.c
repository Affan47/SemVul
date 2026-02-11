settings_impl(void) {

  int state;
  efax_controller.get_state(state);

  if (state != EfaxController::inactive) {
    std::string message(gettext("Can't change settings unless "
				"the program is inactive\n"
				"Press the Stop button to make it inactive"));
    new InfoDialog(message.c_str(), "Change settings",
		   GTK_MESSAGE_WARNING, get_win());


  }

  else {
    SettingsDialog* dialog_p = new SettingsDialog(standard_size, get_win());

    dialog_p->accepted.connect(Callback::make(*this, &MainWindow::settings_changed_cb));


  }
}
