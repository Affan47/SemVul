elantech_show_int_attr(struct psmouse *psmouse, void *data,
					char *buf)
{
	struct elantech_data *etd = psmouse->private;
	struct elantech_attr_data *attr = data;
	unsigned char *reg = (unsigned char *) etd + attr->field_offset;
	int rc = 0;

	if (attr->reg)
		rc = elantech_read_reg(psmouse, attr->reg, reg);

	return sprintf(buf, "0x%02x\n", (attr->reg && rc) ? -1 : *reg);
}
