VGZ_WrwGunzip(const struct sess *sp, struct vgz *vg, const void *ibuf,
    ssize_t ibufl, char *obuf, ssize_t obufl, ssize_t *obufp)
{
	int i;
	size_t dl;
	const void *dp;

	CHECK_OBJ_NOTNULL(vg, VGZ_MAGIC);
	assert(obufl > 16);
	VGZ_Ibuf(vg, ibuf, ibufl);
	if (ibufl == 0)
		return (VGZ_OK);
	VGZ_Obuf(vg, obuf + *obufp, obufl - *obufp);
	do {
		if (obufl == *obufp)
			i = VGZ_STUCK;
		else {
			i = VGZ_Gunzip(vg, &dp, &dl);
			*obufp += dl;
		}
		if (i < VGZ_OK) {

			return (-1);
		}
		if (obufl == *obufp || i == VGZ_STUCK) {
			(void)WRW_Write(sp->wrk, obuf, *obufp);
			(void)WRW_Flush(sp->wrk);
			*obufp = 0;
			VGZ_Obuf(vg, obuf + *obufp, obufl - *obufp);
		}
	} while (!VGZ_IbufEmpty(vg));
	if (i == VGZ_STUCK)
		i = VGZ_OK;
	return (i);
}
