detect_scsi(struct Epson_Scanner *s)
{
	SANE_Status status;
	struct Epson_Device *dev = s->hw;

	char buf[INQUIRY_BUF_SIZE + 1];
	size_t buf_size = INQUIRY_BUF_SIZE;

	char *vendor = buf + 8;
	char *model = buf + 16;
	char *rev = buf + 32;

	status = sanei_epson2_scsi_inquiry(s->fd, buf, &buf_size);
	if (status != SANE_STATUS_GOOD) {
		DBG(1, "%s: inquiry failed: %s\n", __func__,
		    sane_strstatus(status));
		return status;
	}

	buf[INQUIRY_BUF_SIZE] = 0;
	DBG(1, "inquiry data:\n");
	DBG(1, " vendor  : %.8s\n", vendor);
	DBG(1, " model   : %.16s\n", model);
	DBG(1, " revision: %.4s\n", rev);

	if (buf[0] != TYPE_PROCESSOR) {
		DBG(1, "%s: device is not of processor type (%d)\n",
		    __func__, buf[0]);
		return SANE_STATUS_INVAL;
	}

	if (strncmp(vendor, "EPSON", 5) != 0) {
		DBG(1,
		    "%s: device doesn't look like an EPSON scanner\n",
		    __func__);
		return SANE_STATUS_INVAL;
	}

	if (strncmp(model, "SCANNER ", 8) != 0
	    && strncmp(model, "FilmScan 200", 12) != 0
	    && strncmp(model, "Perfection", 10) != 0
	    && strncmp(model, "Expression", 10) != 0
	    && strncmp(model, "GT", 2) != 0) {
		DBG(1, "%s: this EPSON scanner is not supported\n",
		    __func__);
		return SANE_STATUS_INVAL;
	}

	if (strncmp(model, "FilmScan 200", 12) == 0) {
		dev->sane.type = "film scanner";
		e2_set_model(s, (unsigned char *) model, 12);
	}


	sanei_epson2_scsi_test_unit_ready(s->fd);

	return SANE_STATUS_GOOD;
}
