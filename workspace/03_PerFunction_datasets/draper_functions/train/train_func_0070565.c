_next_pgno(int *arg, struct vt_page *vtp)
{
    int pgno = vtp->pgno;

    if (arg[0] == pgno)
	return 0;
    if (arg[1])
	for (; pgno; pgno >>=4)
	    if ((pgno & 15) > 9)
		return 0;
    return 1;
}
