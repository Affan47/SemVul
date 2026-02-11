cb_zerou(GtkAction *action)
{
	int	fd, cnt;
	struct	spcharge	spc;

	if  (!getselectedusers(1))
		return;

	if  (!Confirm(101))
		return;
	if  ((fd = grab_file(O_WRONLY|O_APPEND)) < 0)
		return;
	time(&spc.spch_when);
	spc.spch_what = SPCH_ZERO;
	for  (cnt = 0;  cnt < pendunum;  cnt++)  {
		spc.spch_user = ulist[pendulist[cnt]].spu_user;
		write(fd, (char *) &spc, sizeof(spc));
	}
	close(fd);
}
