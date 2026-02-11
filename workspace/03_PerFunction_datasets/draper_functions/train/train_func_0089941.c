aim_bstream_send(aim_bstream_t *bs, aim_conn_t *conn, size_t count)
{
	int wrote = 0;
	if (!bs || !conn || (count < 0))
		return -EINVAL;

	if (count > aim_bstream_empty(bs))
		count = aim_bstream_empty(bs);

	if (count) {
		if ((conn->type == AIM_CONN_TYPE_RENDEZVOUS) &&
			(conn->subtype == AIM_CONN_SUBTYPE_OFT_DIRECTIM)) {


			const char *sn = aim_odc_getsn(conn);
			aim_rxcallback_t userfunc;
			while (count - wrote > 1024) {
				wrote = wrote + aim_send(conn->fd,
					bs->data + bs->offset + wrote, 1024);
				if ((userfunc = aim_callhandler(conn->sessv,
							conn,
							AIM_CB_FAM_SPECIAL,
							AIM_CB_SPECIAL_IMAGETRANSFER)))
					userfunc(conn->sessv, NULL, sn,
						count - wrote >
						1024 ? ((double)wrote /
							count) : 1);
			}
		}
		if (count - wrote) {
			wrote = wrote + aim_send(conn->fd,
				bs->data + bs->offset + wrote, count - wrote);
		}

	}

	if (((aim_session_t *)conn->sessv)->debug >= 2) {
		int i;
		aim_session_t *sess = (aim_session_t *)conn->sessv;

		faimdprintf(sess, 2, "\nOutgoing data: (%d bytes)", wrote);
		for (i = 0; i < wrote; i++) {
			if (!(i % 8))
				faimdprintf(sess, 2, "\n\t");
			faimdprintf(sess, 2, "0x%02x ",
				*(bs->data + bs->offset + i));
		}
		faimdprintf(sess, 2, "\n");
	}

	bs->offset += wrote;

	return wrote;
}
