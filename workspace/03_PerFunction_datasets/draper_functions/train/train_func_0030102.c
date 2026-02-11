ctx_p2p_start_persistent()
{
	if (ctx_item == NULL)
		return;

	char cmd[100];
	char reply[100];
	size_t reply_len;

	snprintf(cmd, sizeof(cmd), "P2P_GROUP_ADD persistent=%d",
		 ctx_item->data(peer_role_network_id).toInt());
	if (wpagui->ctrlRequest(cmd, reply, &reply_len) < 0 ||
	    memcmp(reply, "FAIL", 4) == 0) {
		QMessageBox msg;
		msg.setIcon(QMessageBox::Warning);
		msg.setText(tr("Failed to start persistent P2P Group."));
		msg.exec();
	} else if (ctx_item->data(peer_role_type).toInt() ==
		   PEER_TYPE_P2P_INVITATION)
		model.removeRow(ctx_item->row());
}
