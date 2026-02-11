json_print_pwr_usb_stats(struct activity *a, int curr, int tab,
					 unsigned long long itv)
{
	int i;
	struct stats_pwr_usb *suc;
	int sep = FALSE;

	if (!IS_SELECTED(a->options) || (a->nr <= 0))
		goto close_json_markup;

	json_markup_power_management(tab, OPEN_JSON_MARKUP);
	tab++;

	xprintf(tab++, "\"usb-devices\": [");

	for (i = 0; i < a->nr; i++) {
		suc = (struct stats_pwr_usb *) ((char *) a->buf[curr]  + i * a->msize);

		if (!suc->bus_nr)

			break;

		if (sep) {
			printf(",\n");
		}
		sep = TRUE;

		xprintf0(tab, "{\"bus_number\": %d, "
			 "\"idvendor\": \"%x\", "
			 "\"idprod\": \"%x\", "
			 "\"maxpower\": %u, "
			 "\"manufact\": \"%s\", "
			 "\"product\": \"%s\"}",
			 suc->bus_nr,
			 suc->vendor_id,
			 suc->product_id,
			 suc->bmaxpower << 1,
			 suc->manufacturer,
			 suc->product);
	}

	printf("\n");
	xprintf0(--tab, "]");
	tab--;

close_json_markup:
	if (CLOSE_MARKUP(a->options)) {
		json_markup_power_management(tab, CLOSE_JSON_MARKUP);
	}
}
