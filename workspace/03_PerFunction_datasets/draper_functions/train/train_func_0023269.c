explode_bitmap_into_buf (PnmLoaderContext *context)
{
	gint j;
	guchar *from, *to, data;
	gint bit;
	guchar *dptr;
	gint wid, x;

	g_return_if_fail (context != NULL);
	g_return_if_fail (context->dptr != NULL);


	dptr = context->dptr;
	wid  = context->width;

	from = dptr + ((wid - 1) / 8);
	to   = dptr + (wid - 1) * 3;
	bit  = 7 - ((wid-1) % 8);


	data = from[0];
	for (j = 0; j < bit; j++, data >>= 1);

	for (x = wid-1; x >= 0; x--) {


		to[0] = to[1] = to[2] = (data & 0x01) ? 0x00 : 0xff;

		to -= 3;
		bit++;

		if (bit > 7 && x > 0) {
			from--;
			data = from[0];
			bit = 0;
		} else {
			data >>= 1;
		}
	}


}
