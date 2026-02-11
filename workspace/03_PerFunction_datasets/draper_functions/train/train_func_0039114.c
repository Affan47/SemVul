st_check_data_len(struct st_data_s *st_gdata,
	unsigned char chnl_id, int len)
{
	int room = skb_tailroom(st_gdata->rx_skb);

	pr_debug("len %d room %d", len, room);

	if (!len) {


		st_send_frame(chnl_id, st_gdata);

	} else if (len > room) {


		pr_err("Data length is too large len %d room %d", len,
			   room);
		kfree_skb(st_gdata->rx_skb);
	} else {


		st_gdata->rx_state = ST_W4_DATA;
		st_gdata->rx_count = len;
		return len;
	}


	st_gdata->rx_state = ST_W4_PACKET_TYPE;
	st_gdata->rx_skb = NULL;
	st_gdata->rx_count = 0;
	st_gdata->rx_chnl = 0;

	return 0;
}
