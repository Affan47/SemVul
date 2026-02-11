print_dev_hdr(struct hci_dev_info *di)
{
	static int hdr = -1;
	char addr[18];

	if (hdr == di->dev_id)
		return;
	hdr = di->dev_id;

	ba2str(&di->bdaddr, addr);

	printf("%s:\tType: %s  Bus: %s\n", di->name,
					hci_typetostr(di->type >> 4),
					hci_bustostr(di->type & 0x0f));
	printf("\tBD Address: %s  ACL MTU: %d:%d  SCO MTU: %d:%d\n",
					addr, di->acl_mtu, di->acl_pkts,
						di->sco_mtu, di->sco_pkts);
}
