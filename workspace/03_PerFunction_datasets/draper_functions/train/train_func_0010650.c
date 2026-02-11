json_print_disk_stats(struct activity *a, int curr, int tab,
				      unsigned long long itv)
{
	int i, j;
	struct stats_disk *sdc,	*sdp;
	struct ext_disk_stats xds;
	int sep = FALSE;
	char *dev_name, *persist_dev_name;

	xprintf(tab++, "\"disk\": [");

	for (i = 0; i < a->nr; i++) {

		sdc = (struct stats_disk *) ((char *) a->buf[curr] + i * a->msize);

		if (!(sdc->major + sdc->minor))
			continue;

		j = check_disk_reg(a, curr, !curr, i);
		sdp = (struct stats_disk *) ((char *) a->buf[!curr] + j * a->msize);


		compute_ext_disk_stats(sdc, sdp, itv, &xds);

		dev_name = NULL;
		persist_dev_name = NULL;

		if (DISPLAY_PERSIST_NAME_S(flags)) {
			persist_dev_name = get_persistent_name_from_pretty(get_devname(sdc->major, sdc->minor, TRUE));
		}

		if (persist_dev_name) {
			dev_name = persist_dev_name;
		}
		else {
			if ((USE_PRETTY_OPTION(flags)) && (sdc->major == dm_major)) {
				dev_name = transform_devmapname(sdc->major, sdc->minor);
			}

			if (!dev_name) {
				dev_name = get_devname(sdc->major, sdc->minor,
						       USE_PRETTY_OPTION(flags));
			}
		}

		if (sep) {
			printf(",\n");
		}
		sep = TRUE;

		xprintf0(tab, "{\"disk-device\": \"%s\", "
			 "\"tps\": %.2f, "
			 "\"rd_sec\": %.2f, "
			 "\"wr_sec\": %.2f, "
			 "\"avgrq-sz\": %.2f, "
			 "\"avgqu-sz\": %.2f, "
			 "\"await\": %.2f, "
			 "\"svctm\": %.2f, "
			 "\"util-percent\": %.2f}",

			 dev_name,
			 S_VALUE(sdp->nr_ios, sdc->nr_ios, itv),
			 ll_s_value(sdp->rd_sect, sdc->rd_sect, itv),
			 ll_s_value(sdp->wr_sect, sdc->wr_sect, itv),

			 xds.arqsz,
			 S_VALUE(sdp->rq_ticks, sdc->rq_ticks, itv) / 1000.0,
			 xds.await,
			 xds.svctm,
			 xds.util / 10.0);
	}

	printf("\n");
	xprintf0(--tab, "]");
}
