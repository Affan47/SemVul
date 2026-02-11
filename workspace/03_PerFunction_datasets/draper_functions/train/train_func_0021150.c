receive_page_button_clicked(GtkWidget* widget_p, void* data) {
  ReceivePage* instance_p = static_cast<ReceivePage*>(data);
  int message_index;
  if (widget_p == instance_p->exec_button_p) {
    instance_p->exec_button_toggled_impl();
    return;
  }
  else if (widget_p == instance_p->popup_help_button_p) {
    message_index = ReceiveMessages::popup;
  }
  else if (widget_p == instance_p->exec_help_button_p) {
    message_index = ReceiveMessages::exec;
  }
  else {
    write_error("Callback error in ReceivePageCB::receive_page_button_clicked()\n");
    return;
  }
  instance_p->show_help_sig(std::pair<std::string, std::string>(
				      instance_p->help_messages.get_message(message_index),
				      instance_p->help_messages.get_caption(message_index)));
}
