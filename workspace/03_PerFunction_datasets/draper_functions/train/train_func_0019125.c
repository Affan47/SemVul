alphix_nix(alphix *p, char *ax) {
	int rv;
	if ((rv = fromanat(p, ax)) < 0)
		return -1;
	return rawtocooked(p, rv);
}
