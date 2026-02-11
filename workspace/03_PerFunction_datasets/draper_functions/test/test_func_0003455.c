set_button_cancel(Gtk::Button& button)
{
  button.signal_clicked().connect(sigc::mem_fun(*this, &Box_WithButtons::on_Button_Cancel));
}
