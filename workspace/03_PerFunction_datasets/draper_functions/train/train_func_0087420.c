st_nci_hci_admin_event_received(struct nci_dev *ndev,
					      u8 event, struct sk_buff *skb)
{
	struct st_nci_info *info = nci_get_drvdata(ndev);

	switch (event) {
	case ST_NCI_EVT_HOT_PLUG:
		if (info->se_info.se_active) {
			if (!ST_NCI_EVT_HOT_PLUG_IS_INHIBITED(skb)) {
				del_timer_sync(&info->se_info.se_active_timer);
				info->se_info.se_active = false;
				complete(&info->se_info.req_completion);
			} else {
				mod_timer(&info->se_info.se_active_timer,
				      jiffies +
				      msecs_to_jiffies(ST_NCI_SE_TO_PIPES));
			}
		}
	break;
	default:
		nfc_err(&ndev->nfc_dev->dev, "Unexpected event on admin gate\n");
	}
}
