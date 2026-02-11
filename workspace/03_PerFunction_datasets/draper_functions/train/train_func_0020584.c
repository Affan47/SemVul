update_all_chars(gpointer data, gpointer user_data)
{
	struct query_data *qdesc, *qvalue;
	struct characteristic *chr = data;
	struct gatt_service *gatt = user_data;

	qdesc = g_new0(struct query_data, 1);
	qdesc->gatt = gatt;
	qdesc->chr = chr;

	query_list_append(gatt, qdesc);

	gatt_find_info(gatt->attrib, chr->handle + 1, chr->end, descriptor_cb,
									qdesc);

	qvalue = g_new0(struct query_data, 1);
	qvalue->gatt = gatt;
	qvalue->chr = chr;

	query_list_append(gatt, qvalue);

	gatt_read_char(gatt->attrib, chr->handle, 0, update_char_value, qvalue);
}
