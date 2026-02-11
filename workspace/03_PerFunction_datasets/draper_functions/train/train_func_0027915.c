st_nci_hci_event_received(struct nci_dev *ndev, u8 pipe,
				 u8 event, struct sk_buff *skb)
{
	u8 gate = ndev->hci_dev->pipes[pipe].gate;
	u8 host = ndev->hci_dev->pipes[pipe].host;

	switch (gate) {
	case NCI_HCI_ADMIN_GATE:
		st_nci_hci_admin_event_received(ndev, event, skb);
	break;
	case ST_NCI_APDU_READER_GATE:
		st_nci_hci_apdu_reader_event_received(ndev, event, skb);
	break;
	case ST_NCI_CONNECTIVITY_GATE:
		st_nci_hci_connectivity_event_received(ndev, host, event, skb);
	break;
	case NCI_HCI_LOOPBACK_GATE:
		st_nci_hci_loopback_event_received(ndev, event, skb);
	break;
	}
}
