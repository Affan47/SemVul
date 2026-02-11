set_isdn_net_ioctl_phone(isdn_net_ioctl_phone *ph, char *name,
			     char *phone, int outflag)
{
	switch (data_version) {
	case 0x04:
	case 0x05:
		if (strlen(phone) > 19) {
			fprintf(stderr, "phone-number must not exceed %d characters\n", 19);
			return -1;
		}


		strncpy(ph->phone_5.name, name, sizeof(ph->phone_5.name)-1);
		strncpy(ph->phone_5.phone, phone, sizeof(ph->phone_5.phone)-1);
		ph->phone_5.outgoing = outflag;
                break;
	case 0x06:
		if (strlen(phone) > 31) {
			fprintf(stderr, "phone-number must not exceed %d characters\n", 31);
			return -1;
		}
		strncpy(ph->phone_6.name, name, sizeof(ph->phone_6.name)-1);
		strncpy(ph->phone_6.phone, phone, sizeof(ph->phone_6.phone)-1);
		ph->phone_6.outgoing = outflag;
	}
	return 0;
}
