trackpoint_show_int_attr(struct psmouse *psmouse, void *data, char *buf)
{
	struct trackpoint_data *tp = psmouse->private;
	struct trackpoint_attr_data *attr = data;
	unsigned char value = *(unsigned char *)((char *)tp + attr->field_offset);

	if (attr->inverted)
		value = !value;

	return sprintf(buf, "%u\n", value);
}
