handlemsg(htmsg *msg)
{
	ht_window::handlemsg(msg);
	if (msg->msg == msg_keypressed) {
		switch (msg->data1.integer) {
		case K_Escape: {
			htmsg m;
			m.type = mt_empty;
			m.msg = cmd_window_close;
			((ht_app*)app)->queuemsg(app, m);
			clearmsg(msg);
			return;
		}
		}
	}
}
