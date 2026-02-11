process_idb_options(pcap_t *p, struct block_cursor *cursor, u_int *tsresol,
    u_int64_t *tsoffset, char *errbuf)
{
	struct option_header *opthdr;
	void *optvalue;
	int saw_tsresol, saw_tsoffset;
	u_char tsresol_opt;
	u_int i;

	saw_tsresol = 0;
	saw_tsoffset = 0;
	while (cursor->data_remaining != 0) {


		opthdr = get_opthdr_from_block_data(p, cursor, errbuf);
		if (opthdr == NULL) {


			return (-1);
		}


		optvalue = get_optvalue_from_block_data(cursor, opthdr,
		    errbuf);
		if (optvalue == NULL) {


			return (-1);
		}

		switch (opthdr->option_code) {

		case OPT_ENDOFOPT:
			if (opthdr->option_length != 0) {
				snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has opt_endofopt option with length %u != 0",
				    opthdr->option_length);
				return (-1);
			}
			goto done;

		case IF_TSRESOL:
			if (opthdr->option_length != 1) {
				snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has if_tsresol option with length %u != 1",
				    opthdr->option_length);
				return (-1);
			}
			if (saw_tsresol) {
				snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has more than one if_tsresol option");
				return (-1);
			}
			saw_tsresol = 1;
			tsresol_opt = *(u_int *)optvalue;
			if (tsresol_opt & 0x80) {


				*tsresol = 1 << (tsresol_opt & 0x7F);
			} else {


				*tsresol = 1;
				for (i = 0; i < tsresol_opt; i++)
					*tsresol *= 10;
			}
			if (*tsresol == 0) {


				if (tsresol_opt & 0x80) {
					snprintf(errbuf, PCAP_ERRBUF_SIZE,
					    "Interface Description Block if_tsresol option resolution 2^-%u is too high",
					    tsresol_opt & 0x7F);
				} else {
					snprintf(errbuf, PCAP_ERRBUF_SIZE,
					    "Interface Description Block if_tsresol option resolution 10^-%u is too high",
					    tsresol_opt);
				}
				return (-1);
			}
			break;

		case IF_TSOFFSET:
			if (opthdr->option_length != 8) {
				snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has if_tsoffset option with length %u != 8",
				    opthdr->option_length);
				return (-1);
			}
			if (saw_tsoffset) {
				snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has more than one if_tsoffset option");
				return (-1);
			}
			saw_tsoffset = 1;
			memcpy(tsoffset, optvalue, sizeof(*tsoffset));
			if (p->sf.swapped)
				*tsoffset = SWAPLL(*tsoffset);
			break;

		default:
			break;
		}
	}

done:
	return (0);
}
