rtl92se_set_desc(struct ieee80211_hw *hw, u8 *pdesc, bool istx,
		      u8 desc_name, u8 *val)
{
	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			wmb();
			SET_TX_DESC_OWN(pdesc, 1);
			break;
		case HW_DESC_TX_NEXTDESC_ADDR:
			SET_TX_DESC_NEXT_DESC_ADDRESS(pdesc, *(u32 *) val);
			break;
		default:
			RT_ASSERT(false, "ERR txdesc :%d not process\n",
				  desc_name);
			break;
		}
	} else {
		switch (desc_name) {
		case HW_DESC_RXOWN:
			wmb();
			SET_RX_STATUS_DESC_OWN(pdesc, 1);
			break;
		case HW_DESC_RXBUFF_ADDR:
			SET_RX_STATUS__DESC_BUFF_ADDR(pdesc, *(u32 *) val);
			break;
		case HW_DESC_RXPKT_LEN:
			SET_RX_STATUS_DESC_PKT_LEN(pdesc, *(u32 *) val);
			break;
		case HW_DESC_RXERO:
			SET_RX_STATUS_DESC_EOR(pdesc, 1);
			break;
		default:
			RT_ASSERT(false, "ERR rxdesc :%d not process\n",
				  desc_name);
			break;
		}
	}
}
