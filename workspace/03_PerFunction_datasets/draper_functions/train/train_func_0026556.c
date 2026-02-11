bcsp_unslip_one_byte(struct bcsp_struct *bcsp, unsigned char byte)
{
	const u8 c0 = 0xc0, db = 0xdb;

	switch (bcsp->rx_esc_state) {
	case BCSP_ESCSTATE_NOESC:
		switch (byte) {
		case 0xdb:
			bcsp->rx_esc_state = BCSP_ESCSTATE_ESC;
			break;
		default:
			memcpy(skb_put(bcsp->rx_skb, 1), &byte, 1);
			if ((bcsp->rx_skb->data[0] & 0x40) != 0 &&
					bcsp->rx_state != BCSP_W4_CRC)
				bcsp_crc_update(&bcsp->message_crc, byte);
			bcsp->rx_count--;
		}
		break;

	case BCSP_ESCSTATE_ESC:
		switch (byte) {
		case 0xdc:
			memcpy(skb_put(bcsp->rx_skb, 1), &c0, 1);
			if ((bcsp->rx_skb->data[0] & 0x40) != 0 &&
					bcsp->rx_state != BCSP_W4_CRC)
				bcsp_crc_update(&bcsp->message_crc, 0xc0);
			bcsp->rx_esc_state = BCSP_ESCSTATE_NOESC;
			bcsp->rx_count--;
			break;

		case 0xdd:
			memcpy(skb_put(bcsp->rx_skb, 1), &db, 1);
			if ((bcsp->rx_skb->data[0] & 0x40) != 0 &&
					bcsp->rx_state != BCSP_W4_CRC)
				bcsp_crc_update(&bcsp->message_crc, 0xdb);
			bcsp->rx_esc_state = BCSP_ESCSTATE_NOESC;
			bcsp->rx_count--;
			break;

		default:
			BT_ERR("Invalid byte %02x after esc byte", byte);
			kfree_skb(bcsp->rx_skb);
			bcsp->rx_skb = NULL;
			bcsp->rx_state = BCSP_W4_PKT_DELIMITER;
			bcsp->rx_count = 0;
		}
	}
}
