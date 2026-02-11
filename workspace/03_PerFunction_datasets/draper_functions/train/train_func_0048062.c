qib_disarm_7220_senderrbufs(struct qib_pportdata *ppd)
{
	unsigned long sbuf[3];
	struct qib_devdata *dd = ppd->dd;


	sbuf[0] = qib_read_kreg64(dd, kr_sendbuffererror);
	sbuf[1] = qib_read_kreg64(dd, kr_sendbuffererror + 1);
	sbuf[2] = qib_read_kreg64(dd, kr_sendbuffererror + 2);

	if (sbuf[0] || sbuf[1] || sbuf[2])
		qib_disarm_piobufs_set(dd, sbuf,
				       dd->piobcnt2k + dd->piobcnt4k);
}
