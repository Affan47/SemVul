gpsdata_add(struct cc_gpsdata *data, struct cc_gpselt *elt)
{
	struct cc_gpselt	*newdata;
	int			newsize;
	if (data->size == data->num) {
		if (data->size == 0)
			newdata = malloc((newsize = 256) * sizeof (struct cc_gpselt));
		else
			newdata = realloc (data->data, (newsize = data->size * 2)
					   * sizeof (struct cc_gpselt));
		if (!newdata)
			return 0;
		data->size = newsize;
		data->data = newdata;
	}
	elt->time += data->time_offset;
	if (data->num && data->data[data->num-1].time > elt->time) {
		data->time_offset += 65536;
		elt->time += 65536;
	}
	data->data[data->num] = *elt;
	data->num++;
	return 1;
}
