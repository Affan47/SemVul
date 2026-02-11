filter_attrs (PangoAttribute *attr, gpointer _data)
{
	struct draw_attrs *data = static_cast <struct draw_attrs *> (_data);
	if (attr->start_index <= data->index && attr->end_index > data->index) {
		PangoAttribute *new_attr = pango_attribute_copy (attr);
		new_attr->start_index = 0;
		new_attr->end_index = data->length;
		pango_attr_list_insert (data->attrs, new_attr);
	}
	return false;
}
