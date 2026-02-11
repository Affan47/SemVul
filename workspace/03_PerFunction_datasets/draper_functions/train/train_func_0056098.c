dccrec_sizeof(dccrec *d)
{
	u_long	tot = 0L;

	tot += sizeof(dccrec);
	tot += d->nick ? strlen(d->nick)+1 : 0L;
	tot += d->uh ? strlen(d->uh)+1 : 0L;
	tot += d->logchname ? strlen(d->logchname)+1 : 0L;
	tot += d->filename ? strlen(d->filename)+1 : 0L;
	tot += d->buf ? strlen(d->buf)+1 : 0L;
	tot += d->from ? strlen(d->from)+1 : 0L;
	tot += d->command ? strlen(d->command)+1 : 0L;
	tot += d->commandfromnick ? strlen(d->commandfromnick)+1 : 0L;

	return tot;
}
