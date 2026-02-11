draw()
{
	clear(getcolor(palidx_generic_body));
	int c = lines->count();
	for (int i=0; i < size.h; i++) {
		if (i+ofs >= c) break;
		ht_log_msg *msg = (ht_log_msg*)(*lines)[i+ofs];
		int l = strlen(msg->msg);
		if (xofs < l) buf->print(0, i, msg->color, msg->msg+xofs);
	}
}
