CFC_filter_duplicate_iv() {
	unsigned char * ivs_table;
	int nb_packets = 0;
	puts("Cloaking - Duplicate IV filtering");

	ivs_table = (unsigned char *) calloc(16777215, 1);
	if (ivs_table == NULL) {
		puts("Failed to allocate memory for IVs table, exiting");
		exit(-1);
	}


	reset_current_packet_pointer();
	do {
		if (_packet_elt_head->current->frame_type == FRAME_TYPE_DATA) {


			*(ivs_table + get_iv(_packet_elt_head->current)) += 1;
		}
	} while (next_packet_pointer() == true);


	reset_current_packet_pointer();
	do {
		if (_packet_elt_head->current->frame_type == FRAME_TYPE_DATA) {

			switch (_packet_elt_head->current->is_cloaked) {
				case POTENTIALLY_CLOAKED_FRAME:

					if (*(ivs_table + get_iv(_packet_elt_head->current)) > 1) {
						_packet_elt_head->current->is_cloaked = CLOAKED_FRAME;
						++nb_packets;
					}
				case UKNOWN_FRAME_CLOAKING_STATUS:

					if (*(ivs_table + get_iv(_packet_elt_head->current)) > 1) {
						_packet_elt_head->current->is_cloaked = POTENTIALLY_CLOAKED_FRAME;
					}
					break;
				case VALID_FRAME_UNCLOAKED:
					break;
				case CLOAKED_FRAME:
					break;
				default:
					break;
			}

		}
	} while (next_packet_pointer() == true);

	free(ivs_table);

	return nb_packets;
}
