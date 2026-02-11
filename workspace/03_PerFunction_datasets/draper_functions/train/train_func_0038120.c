new_icmTextDescription(
	icc *icp
) {
	icmTextDescription *p;
	if ((p = (icmTextDescription *) icp->al->calloc(icp->al,1,sizeof(icmTextDescription))) == NULL)
		return NULL;

	icmTextDescription_init(p,icp);
	return (icmBase *)p;
}
