icmCurve_allocate(
	icmBase *pp
) {
	icmCurve *p = (icmCurve *)pp;
	icc *icp = p->icp;

	if (p->flag == icmCurveUndef) {
		sprintf(icp->err,"icmCurve_alloc: flag not set");
		return icp->errc = 1;
	} else if (p->flag == icmCurveLin) {
		p->size = 0;
	} else if (p->flag == icmCurveGamma) {
		p->size = 1;
	}
	if (p->size != p->_size) {
		if (ovr_mul(p->size, sizeof(double))) {
			sprintf(icp->err,"icmCurve_alloc: size overflow");
			return icp->errc = 1;
		}
		if (p->data != NULL)
			icp->al->free(icp->al, p->data);
		if ((p->data = (double *) icp->al->calloc(icp->al, p->size, sizeof(double))) == NULL) {
			sprintf(icp->err,"icmCurve_alloc: malloc() of icmCurve data failed");
			return icp->errc = 2;
		}
		p->_size = p->size;
	}
	return 0;
}
