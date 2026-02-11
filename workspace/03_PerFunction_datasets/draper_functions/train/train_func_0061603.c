show_device_property_dialog(const std::string& filename)
{
  Joystick* joystick = new Joystick(filename);
  JoystickTestWidget* dialog = new JoystickTestWidget(*joystick);
  dialog->signal_hide().connect(sigc::bind(sigc::mem_fun(this, &Main::on_dialog_hide), dialog));
  dialog->show_all();
  joysticks.push_back(joystick);
  dialogs.push_back(dialog);
}
