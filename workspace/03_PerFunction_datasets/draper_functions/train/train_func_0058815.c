buf_write_ccmx(
ccmx *p,
unsigned char **buf,
int *len
) {
	int rv;
	cgats *ocg;
	cgatsFile *fp;


	if ((rv = create_ccmx_cgats(p, &ocg)) != 0) {
		return rv;
	}

	if ((fp = new_cgatsFileMem(NULL, 0)) == NULL) {
		strcpy(p->err, "new_cgatsFileMem failed");
		return 2;
	}


	if (ocg->write(ocg, fp)) {
		strcpy(p->err, ocg->err);
		ocg->del(ocg);
		fp->del(fp);
		return 1;
	}


	if (fp->get_buf(fp, buf, (size_t *)len)) {
		strcpy(p->err, "cgatsFileMem get_buf failed");
		return 2;
	}

	ocg->del(ocg);
	fp->del(fp);

	return 0;
}
