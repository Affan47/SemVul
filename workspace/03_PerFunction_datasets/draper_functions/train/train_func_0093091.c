cb_splice (PangoAttribute *attr, gpointer _data)
{
	struct cb_splice *data = _data;

	if (attr->start_index >= data->pos) {
		PangoAttribute *new_attr = pango_attribute_copy (attr);
		new_attr->start_index += data->len;
		new_attr->end_index += data->len;
		pango_attr_list_insert (data->result, new_attr);
	} else if (attr->end_index <= data->pos) {
		PangoAttribute *new_attr = pango_attribute_copy (attr);
		pango_attr_list_insert (data->result, new_attr);
	} else {
		PangoAttribute *new_attr = pango_attribute_copy (attr);
		new_attr->end_index = data->pos;
		pango_attr_list_insert (data->result, new_attr);

		new_attr = pango_attribute_copy (attr);
		new_attr->start_index = data->pos + data->len;
		new_attr->end_index += data->len;
		pango_attr_list_insert (data->result, new_attr);
	}

	return FALSE;
}
