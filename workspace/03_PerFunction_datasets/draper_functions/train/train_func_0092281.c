enter_pin()
{
	if (ctx_item == NULL)
		return;

	int peer_type = ctx_item->data(peer_role_type).toInt();
	QString uuid;
	QString addr;
	addr = ctx_item->data(peer_role_address).toString();
	if (peer_type == PEER_TYPE_WPS_ER_ENROLLEE)
		uuid = ctx_item->data(peer_role_uuid).toString();

	StringQuery input(tr("PIN:"));
	input.setWindowTitle(tr("PIN for ") + ctx_item->text());
	if (input.exec() != QDialog::Accepted)
		return;

	char cmd[100];
	char reply[100];
	size_t reply_len;

	if (peer_type == PEER_TYPE_WPS_ER_ENROLLEE) {
		snprintf(cmd, sizeof(cmd), "WPS_ER_PIN %s %s %s",
			 uuid.toAscii().constData(),
			 input.get_string().toAscii().constData(),
			 addr.toAscii().constData());
	} else {
		snprintf(cmd, sizeof(cmd), "WPS_PIN %s %s",
			 addr.toAscii().constData(),
			 input.get_string().toAscii().constData());
	}
	reply_len = sizeof(reply) - 1;
	if (wpagui->ctrlRequest(cmd, reply, &reply_len) < 0) {
		QMessageBox msg;
		msg.setIcon(QMessageBox::Warning);
		msg.setText(tr("Failed to set the WPS PIN."));
		msg.exec();
	}
}
