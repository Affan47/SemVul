blksum(double *sum, double *sumsq)
{
	unsigned char buf[80];
	if (markv(1)) {
		P *q = pdup(markb, USTR "blksum");
		int x;
		int c;
		double accu = 0.0;
		double accusq = 0.0;
		double v;
		int count = 0;
		long left = markb->xcol;
		long right = markk->xcol;
		while (q->byte < markk->byte) {

			while (q->byte < markk->byte && square && (piscol(q) < left || piscol(q) >= right))
				pgetc(q);


			while (q->byte < markk->byte && (!square || (piscol(q) >= left && piscol(q) < right))) {
				c=pgetc(q);
				if ((c >= '0' && c <= '9') || c == '.' || c == '-') {

					buf[0]=c; x=1;
					while (q->byte < markk->byte && (!square || (piscol(q) >= left && piscol(q) < right))) {
						c=pgetc(q);
						if ((c >= '0' && c <= '9') || c == 'e' || c == 'E' ||
						    c == 'p' || c == 'P' || c == 'x' || c == 'X' ||
						    c == '.' || c == '-' || c == '+' ||
						    (c >= 'a' && c <= 'f') || (c >= 'A' && c<='F')) {
							if(x != 79)
								buf[x++]=c;
						} else
							break;
					}

					buf[x] = 0;
					v = strtod((char *)buf,NULL);
					++count;
					accu += v;
					accusq += v*v;
					break;
				}
			}
		}
		prm(q);
		*sum = accu;
		*sumsq = accusq;
		return count;
	} else
		return -1;
}
