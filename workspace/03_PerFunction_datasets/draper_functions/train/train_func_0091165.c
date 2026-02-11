blkget()
{
	if (markv(1)) {
		P *q;
		unsigned char *buf=joe_malloc(markk->byte-markb->byte+1);
		unsigned char *s=buf;
		long left = markb->xcol;
		long right = markk->xcol;
		q = pdup(markb, USTR "blkget");
		while (q->byte < markk->byte) {

			while (q->byte < markk->byte && square && (piscol(q) < left || piscol(q) >= right))
				pgetc(q);


			while (q->byte < markk->byte && (!square || (piscol(q) >= left && piscol(q) < right))) {
				*s++ = pgetc(q);
			}

			if (square && q->byte<markk->byte && piscol(q) >= right)
				*s++ = '\n';
		}
		prm(q);
		*s = 0;
		return buf;
	} else
		return 0;
}
