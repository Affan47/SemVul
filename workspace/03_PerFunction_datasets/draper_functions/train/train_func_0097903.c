packet_hci_event(struct timeval *tv, uint16_t index,
					const void *data, uint16_t size)
{
	const hci_event_hdr *hdr = data;

	btsnoop_write(tv, index, 0x03, data, size);

	print_header(tv, index);

	if (size < HCI_EVENT_HDR_SIZE) {
		printf("* Malformed HCI Event packet\n");
		return;
	}

	printf("> HCI Event: %s (0x%2.2x) plen %d\n",
				event2str(hdr->evt), hdr->evt, hdr->plen);

	data += HCI_EVENT_HDR_SIZE;
	size -= HCI_EVENT_HDR_SIZE;

	packet_hexdump(data, size);
}
