ajax_get_messages(struct mg_connection *conn,
                              const struct mg_request_info *request_info) {
char src_addr[20];


	dispwin *p = (dispwin *)mg_get_user_data(conn);


	p->ccix++;

	while(p->ncix == p->ccix && p->mg_stop == 0) {
		msec_sleep(50);
	}

	mg_printf(conn,
			"\r\n#%02X%02X%02X",
			(int)(p->r_rgb[0] * 255.0 + 0.5),
			(int)(p->r_rgb[1] * 255.0 + 0.5),
			(int)(p->r_rgb[2] * 255.0 + 0.5));
}
