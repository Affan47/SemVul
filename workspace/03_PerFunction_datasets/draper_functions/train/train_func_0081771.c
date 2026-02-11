ctx_p2p_listen()
{
	char reply[20];
	size_t reply_len;
	reply_len = sizeof(reply) - 1;
	if (wpagui->ctrlRequest("P2P_LISTEN 3600", reply, &reply_len) < 0 ||
	    memcmp(reply, "FAIL", 4) == 0) {
		QMessageBox msg;
		msg.setIcon(QMessageBox::Warning);
		msg.setText("Failed to start P2P listen.");
		msg.exec();
	}
}
