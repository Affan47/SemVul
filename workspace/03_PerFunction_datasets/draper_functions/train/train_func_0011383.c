floppy_gen_floppydrive_writedata(
	void *s,
	unsigned char *buf,
	unsigned int bufsize
)
{
	struct cpssp *cpssp = (struct cpssp *) s;

	if (DEBUG_CONTROL_FLOW) {
		fprintf(stderr, "%s\n", __FUNCTION__);
	}

	if (! cpssp->select) {
		return;
	}

	memcpy(cpssp->buffer, buf, bufsize);
	cpssp->bufsize = bufsize;
	switch (cpssp->op) {
	case DRIVE_NONE:
		cpssp->op = DRIVE_WRITE;
		floppy_gen_floppydrive_step(cpssp);
		break;
	case DRIVE_READ_DONE:
	case DRIVE_WRITE_DONE:
		cpssp->op = DRIVE_WRITE;
		break;
	default:
		assert(0);
	}
}
