slc_end_reply()
{
    int len;


    if (&slc_replyp[2] > slc_reply_eom)
            return;
    *slc_replyp++ = IAC;
    *slc_replyp++ = SE;
    len = slc_replyp - slc_reply;
    if (len <= 6)
	return;
    if (NETROOM() > len) {
	ring_supply_data(&netoring, slc_reply, slc_replyp - slc_reply);
	printsub('>', &slc_reply[2], slc_replyp - slc_reply - 2);
    }
else printf("slc_end_reply: not enough room\n");
}
