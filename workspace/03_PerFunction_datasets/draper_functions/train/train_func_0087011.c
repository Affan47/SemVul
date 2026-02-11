parse_descriptors(enum table_type t, const unsigned char *buf,
							  int descriptors_loop_len, void *data)
{
	while (descriptors_loop_len > 0) {
		unsigned char descriptor_tag = getBits(buf, 0, 8);
		unsigned char descriptor_len = getBits(buf, 8, 8) + 2;

		if (!descriptor_len) {
			warning("descriptor_tag == 0x%02X, len is 0\n", descriptor_tag);
			break;
		}

		switch(descriptor_tag)
		{
		case 0x09:
			if (t == PMT)
				parse_ca_descriptor (buf, data);
			break;

		case 0x0a:
			if (t == PMT)
				parse_iso639_language_descriptor (buf, data);
			break;

		case 0x40:
			if (t == NIT)
				parse_network_name_descriptor (buf, data);
			break;

		case 0x43:
			if (t == NIT)
				parse_satellite_delivery_system_descriptor (buf, data);
			break;

		case 0x79:
			info("ERROR: S2_satellite_delivery_system_descriptor not parsed\n");
			if( t == NIT)
				parse_s2_satellite_delivery_system_descriptor (buf, data);
			break;

		case 0x44:
			if (t == NIT)
				parse_cable_delivery_system_descriptor (buf, data);
			break;

		case 0x48:
			if (t == SDT)
				parse_service_descriptor (buf, data);
			break;

		case 0x53:
			if (t == SDT)
				parse_ca_identifier_descriptor (buf, data);
			break;

		case 0x5a:
			if (t == NIT)
				parse_terrestrial_delivery_system_descriptor (buf, data);
			break;

		case 0x62:
			if (t == NIT)
				parse_frequency_list_descriptor (buf, data);
			break;

		case 0x83:


			if (t == NIT && vdr_dump_channum)
				parse_terrestrial_uk_channel_number (buf, data);
			break;

		default:
			verbosedebug("skip descriptor 0x%02X\n", descriptor_tag);
		};

		buf += descriptor_len;
		descriptors_loop_len -= descriptor_len;
	}
}
