menu_item_activated(GtkMenuItem* item_p, void* data) {
    TrayIcon* instance_p = static_cast<TrayIcon*>(data);

    if (item_p == instance_p->list_received_faxes_item_p) {
      instance_p->menu_item_chosen(TrayIcon::list_received_faxes);
    }
    else if (item_p == instance_p->list_sent_faxes_item_p) {
      instance_p->menu_item_chosen(TrayIcon::list_sent_faxes);
    }
    else if (item_p == instance_p->redial_queue_item_p) {
      instance_p->menu_item_chosen(TrayIcon::redial_queue);
    }
    else if (item_p == instance_p->receive_takeover_item_p) {
      instance_p->menu_item_chosen(TrayIcon::receive_takeover);
    }
    else if (item_p == instance_p->receive_answer_item_p) {
      instance_p->menu_item_chosen(TrayIcon::receive_answer);
    }
    else if (item_p == instance_p->receive_standby_item_p) {
      instance_p->menu_item_chosen(TrayIcon::receive_standby);
    }
    else if (item_p == instance_p->stop_item_p) {
      instance_p->menu_item_chosen(TrayIcon::stop);
    }
    else if (item_p == instance_p->quit_item_p) {
      instance_p->menu_item_chosen(TrayIcon::quit);
    }
    else {
      write_error("Callback error in TrayIcon::CB::menu_item_activated()\n");
    }
  }
