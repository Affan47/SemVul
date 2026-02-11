unblock()
{
	if (ui_.sw_register->currentWidget() == ui_.page_server) {
		ui_.gb_server->setEnabled(true);
		ui_.gb_connection->setEnabled(true);
		ui_.pb_next->setEnabled(true);
	}
	else if (ui_.sw_register->currentWidget() == ui_.page_fields) {
		ui_.pb_next->setEnabled(true);
		if (fields_)
			fields_->setEnabled(true);
	}
}
