ipmi_sdr_dump_bin(struct ipmi_intf *intf, const char *ofile)
{
	struct sdr_get_rs *header;
	struct ipmi_sdr_iterator *itr;
	struct sdr_record_list *sdrr;
	FILE *fp;
	int rc = 0;


	itr = ipmi_sdr_start(intf, 0);
	if (itr == NULL) {
		lprintf(LOG_ERR, "Unable to open SDR for reading");
		return -1;
	}

	printf("Dumping Sensor Data Repository to '%s'\n", ofile);


	while ((header = ipmi_sdr_get_next_header(intf, itr)) != NULL) {
		sdrr = malloc(sizeof(struct sdr_record_list));
		if (sdrr == NULL) {
			lprintf(LOG_ERR, "ipmitool: malloc failure");
			return -1;
		}
		memset(sdrr, 0, sizeof(struct sdr_record_list));

		lprintf(LOG_INFO, "Record ID %04x (%d bytes)",
			header->id, header->length);

		sdrr->id = header->id;
		sdrr->version = header->version;
		sdrr->type = header->type;
		sdrr->length = header->length;
		sdrr->raw = ipmi_sdr_get_record(intf, header, itr);

		if (sdrr->raw == NULL) {
		    lprintf(LOG_ERR, "ipmitool: cannot obtain SDR record %04x", header->id);
		    return -1;
		}

		if (sdr_list_head == NULL)
			sdr_list_head = sdrr;
		else
			sdr_list_tail->next = sdrr;

		sdr_list_tail = sdrr;
	}

	ipmi_sdr_end(intf, itr);


	fp = ipmi_open_file_write(ofile);
	if (fp == NULL)
		return -1;

	for (sdrr = sdr_list_head; sdrr != NULL; sdrr = sdrr->next) {
		int r;
		uint8_t h[5];


		h[0] = sdrr->id & 0xff;
		h[1] = (sdrr->id >> 8) & 0xff;
		h[2] = sdrr->version;
		h[3] = sdrr->type;
		h[4] = sdrr->length;

		r = fwrite(h, 1, 5, fp);
		if (r != 5) {
			lprintf(LOG_ERR, "Error writing header "
				"to output file %s", ofile);
			rc = -1;
			break;
		}


		if (!sdrr->raw) {
			lprintf(LOG_ERR, "Error: raw data is null (length=%d)",
								sdrr->length);
			rc = -1;
			break;
		}
		r = fwrite(sdrr->raw, 1, sdrr->length, fp);
		if (r != sdrr->length) {
			lprintf(LOG_ERR, "Error writing %d record bytes "
				"to output file %s", sdrr->length, ofile);
			rc = -1;
			break;
		}
	}
	fclose(fp);

	return rc;
}
