write_NamedColorVal(
	icmNamedColorVal *p,
	char *d,
	icColorSpaceSignature pcs,
	unsigned int ndc
) {
	icc *icp = p->icp;
	unsigned int i;
	int rv;

	if ((rv = check_null_string(p->root,32)) == 1) {
		sprintf(icp->err,"icmNamedColorVal_write: Root string names is unterminated");
		return icp->errc = 1;
	}
	strcpy(d, p->root);
	d += strlen(p->root) + 1;
	for (i = 0; i < ndc; i++) {
		if ((rv = write_DCS8Number(p->deviceCoords[i], d)) != 0) {
			sprintf(icp->err,"icmNamedColorVal_write: write of device coord failed");
			return icp->errc = 1;
		}
		d += 1;
	}
	return 0;
}
