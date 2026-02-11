drawline (int n, PRN *prn)
{
    int t;

    pputs(prn, "       |+");
    for (t=1; t<=n; t++) {
	pputc(prn, (t % 10)? '-' : '+');
    }
    pputc(prn, '\n');
}
