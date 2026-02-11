proto_parse_ack(IrmoClient *client, unsigned int ack)
{
	unsigned int seq;
	unsigned int relative;


	seq = get_stream_position(client->sendwindow_start, ack);


        if (seq <= client->sendwindow_start) {
                return;
        }

	relative = seq - client->sendwindow_start;


	if ((unsigned) relative > client->sendwindow_size) {


		return;
	}


        proto_update_cc_values(client);
        advance_send_window(client, relative);
}
