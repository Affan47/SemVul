mc_set_model(Magicolor_Scanner * s, const char *model, size_t len)
{
	unsigned char *buf;
	unsigned char *p;
	struct Magicolor_Device *dev = s->hw;

	buf = malloc(len + 1);
	if (buf == NULL)
		return SANE_STATUS_NO_MEM;

	memcpy(buf, model, len);
	buf[len] = '\0';

	p = &buf[len - 1];

	while (*p == ' ') {
		*p = '\0';
		p--;
	}

	if (dev->model)
		free(dev->model);

	dev->model = strndup((const char *) buf, len);
	dev->sane.model = dev->model;
	DBG(10, "%s: model is '%s'\n", __func__, dev->model);

	free(buf);

	return SANE_STATUS_GOOD;
}
