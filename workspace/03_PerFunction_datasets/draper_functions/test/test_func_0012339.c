num_completed_packets(struct btdev *btdev)
{
	if (btdev->conn) {
		struct bt_hci_evt_num_completed_packets ncp;

		ncp.num_handles = 1;
		ncp.handle = cpu_to_le16(42);
		ncp.count = cpu_to_le16(1);

		send_event(btdev, BT_HCI_EVT_NUM_COMPLETED_PACKETS,
							&ncp, sizeof(ncp));
	}
}
