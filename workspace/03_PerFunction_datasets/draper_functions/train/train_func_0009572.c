ActivityMeter() : dialog(_("Please wait..."), true, true) {
  loop = Glib::MainLoop::create();
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.get_vbox()->pack_start(bar, true, true);
  bar.set_pulse_step(0.007);
  dialog.signal_response().connect(sigc::mem_fun(this, &ActivityMeter::signal_response_cb));
}
