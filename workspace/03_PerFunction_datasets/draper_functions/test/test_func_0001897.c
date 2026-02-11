elantech_set_int_attr(struct psmouse *psmouse,
				     void *data, const char *buf, size_t count)
{
	struct elantech_data *etd = psmouse->private;
	struct elantech_attr_data *attr = data;
	unsigned char *reg = (unsigned char *) etd + attr->field_offset;
	unsigned char value;
	int err;

	err = kstrtou8(buf, 16, &value);
	if (err)
		return err;


	if (etd->hw_version == 1) {
		if (attr->reg == 0x10)

			value |= ETP_R10_ABSOLUTE_MODE;
		else if (attr->reg == 0x11)

			value |= ETP_R11_4_BYTE_MODE;
	}

	if (!attr->reg || elantech_write_reg(psmouse, attr->reg, value) == 0)
		*reg = value;

	return count;
}
