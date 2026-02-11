log_ar_at_event(struct fw_ohci *ohci,
			    char dir, int speed, u32 *header, int evt)
{
	int tcode = header[0] >> 4 & 0xf;
	char specific[12];

	if (likely(!(param_debug & OHCI_PARAM_DEBUG_AT_AR)))
		return;

	if (unlikely(evt >= ARRAY_SIZE(evts)))
			evt = 0x1f;

	if (evt == OHCI1394_evt_bus_reset) {
		ohci_notice(ohci, "A%c evt_bus_reset, generation %d\n",
			    dir, (header[2] >> 16) & 0xff);
		return;
	}

	switch (tcode) {
	case 0x0: case 0x6: case 0x8:
		snprintf(specific, sizeof(specific), " = %08x",
			 be32_to_cpu((__force __be32)header[3]));
		break;
	case 0x1: case 0x5: case 0x7: case 0x9: case 0xb:
		snprintf(specific, sizeof(specific), " %x,%x",
			 header[3] >> 16, header[3] & 0xffff);
		break;
	default:
		specific[0] = '\0';
	}

	switch (tcode) {
	case 0xa:
		ohci_notice(ohci, "A%c %s, %s\n",
			    dir, evts[evt], tcodes[tcode]);
		break;
	case 0xe:
		ohci_notice(ohci, "A%c %s, PHY %08x %08x\n",
			    dir, evts[evt], header[1], header[2]);
		break;
	case 0x0: case 0x1: case 0x4: case 0x5: case 0x9:
		ohci_notice(ohci,
			    "A%c spd %x tl %02x, %04x -> %04x, %s, %s, %04x%08x%s\n",
			    dir, speed, header[0] >> 10 & 0x3f,
			    header[1] >> 16, header[0] >> 16, evts[evt],
			    tcodes[tcode], header[1] & 0xffff, header[2], specific);
		break;
	default:
		ohci_notice(ohci,
			    "A%c spd %x tl %02x, %04x -> %04x, %s, %s%s\n",
			    dir, speed, header[0] >> 10 & 0x3f,
			    header[1] >> 16, header[0] >> 16, evts[evt],
			    tcodes[tcode], specific);
	}
}
