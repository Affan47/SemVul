show_available_datatypes(struct most_c_obj *c,
					struct most_c_attr *attr,
					char *buf)
{
	unsigned int i = c->channel_id;

	strcpy(buf, "");
	if (c->iface->channel_vector[i].data_type & MOST_CH_CONTROL)
		strcat(buf, "control ");
	if (c->iface->channel_vector[i].data_type & MOST_CH_ASYNC)
		strcat(buf, "async ");
	if (c->iface->channel_vector[i].data_type & MOST_CH_SYNC)
		strcat(buf, "sync ");
	if (c->iface->channel_vector[i].data_type & MOST_CH_ISOC_AVP)
		strcat(buf, "isoc_avp ");
	strcat(buf, "\n");
	return strlen(buf) + 1;
}
