dobuild(BW *bw, unsigned char *s, void *object, int *notify)
{
	unsigned char **a = vamk(10);
	unsigned char *cmd = vsncpy(NULL, 0, sc("/bin/sh"));

	a = vaadd(a, cmd);
	cmd = vsncpy(NULL, 0, sc("-c"));
	a = vaadd(a, cmd);
	a = vaadd(a, s);
	return cstart(bw, USTR "/bin/sh", a, NULL, notify, 1, 0);
}
