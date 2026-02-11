excel_read_LABEL_markup (BiffQuery *q, ExcelReadSheet *esheet,
			 char const *str, unsigned str_len)
{
	guint8 const * const end  = q->data + q->length;
	guint8 const *ptr = q->data + 8 + str_len;
	MSContainer const *c = &esheet->container;
	TXORun txo_run;
	unsigned n;
	unsigned int clen = g_utf8_strlen (str, -1);

	d (0, {
			g_printerr ("strlen=%d len=%d\n", str_len, (int)strlen (str));
			ms_biff_query_dump (q);
		});

	txo_run.last = G_MAXINT;

	if (esheet_ver (esheet) >= MS_BIFF_V8) {
		XL_CHECK_CONDITION_VAL (ptr+2 <= end , NULL);
		n = 4 * GSF_LE_GET_GUINT16 (ptr);
		ptr += 2;

		XL_CHECK_CONDITION_VAL (ptr + n == end , NULL);

		txo_run.accum = pango_attr_list_new ();
		while (n > 0) {
			guint16 o,l;

			n -= 4;

			o = GSF_LE_GET_GUINT16 (ptr + n);
			l = GSF_LE_GET_GUINT16 (ptr + n + 2);
			XL_CHECK_CONDITION_VAL (o <= clen,
						go_format_new_markup (txo_run.accum, FALSE));

			txo_run.first = g_utf8_offset_to_pointer (str, o) - str;
			XL_CHECK_CONDITION_VAL (txo_run.first < txo_run.last,
						go_format_new_markup (txo_run.accum, FALSE));

			pango_attr_list_filter (ms_container_get_markup (c, l),
						(PangoAttrFilterFunc) append_markup,
						&txo_run);
			txo_run.last = txo_run.first;
		}
	} else {
		XL_CHECK_CONDITION_VAL (ptr+1 <= end , NULL);
		n = 2 * GSF_LE_GET_GUINT8 (ptr);
		ptr += 1;

		XL_CHECK_CONDITION_VAL (ptr + n == end , NULL);

		txo_run.accum = pango_attr_list_new ();
		while (n > 0) {
			n -= 2;
			txo_run.first = g_utf8_offset_to_pointer (str,
								  GSF_LE_GET_GUINT8 (ptr + n)) - str;
			pango_attr_list_filter (ms_container_get_markup (
									 c, GSF_LE_GET_GUINT8 (ptr + n + 1)),
						(PangoAttrFilterFunc) append_markup, &txo_run);
			txo_run.last = txo_run.first;
		}
	}
	return go_format_new_markup (txo_run.accum, FALSE);
}
