render_pwr_usb_stats(struct activity *a, int isdb, char *pre,
				     int curr, unsigned long long itv)
{
	int i;
	struct stats_pwr_usb *suc;
	char id[9];

	for (i = 0; i < a->nr; i++) {
		suc = (struct stats_pwr_usb *) ((char *) a->buf[curr] + i * a->msize);

		if (!suc->bus_nr)

			break;

		sprintf(id, "%x", suc->vendor_id);
		render(isdb, pre, PT_USESTR,
		       "bus%d\tidvendor",
		       "%d",
		       cons(iv, suc->bus_nr, NOVAL),
		       NOVAL,
		       NOVAL,
		       id);

		sprintf(id, "%x", suc->product_id);
		render(isdb, pre, PT_USESTR,
		       "bus%d\tidprod",
		       NULL,
		       cons(iv, suc->bus_nr, NOVAL),
		       NOVAL,
		       NOVAL,
		       id);

		render(isdb, pre, PT_USEINT,
		       "bus%d\tmaxpower",
		       NULL,
		       cons(iv, suc->bus_nr, NOVAL),
		       suc->bmaxpower << 1,
		       NOVAL,
		       NULL);

		render(isdb, pre, PT_USESTR,
		       "bus%d\tmanufact",
		       NULL,
		       cons(iv, suc->bus_nr, NOVAL),
		       NOVAL,
		       NOVAL,
		       suc->manufacturer);

		render(isdb, pre,
		       (DISPLAY_HORIZONTALLY(flags) ? PT_USESTR : PT_USESTR | PT_NEWLIN),
		       "bus%d\tproduct",
		       NULL,
		       cons(iv, suc->bus_nr, NOVAL),
		       NOVAL,
		       NOVAL,
		       suc->product);
	}
}
