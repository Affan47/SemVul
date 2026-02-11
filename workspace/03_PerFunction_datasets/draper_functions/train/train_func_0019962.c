printZlm(Zlm* zlm)
{
	gint i;
	printf("%22s%d%s%d%s\n","Coefficients of Z(",zlm->l,",",zlm->m,")");
	printf("%15s%5s%5s%5s\n","************","****","****","****");
	printf("%15s%5s%5s%5s\n","Coefficients","lx","ly","lz");
	printf("%15s%5s%5s%5s\n","************","****","****","****");
	for(i=0; i<zlm->numberOfCoefficients; i++)
		printf("%15.8f%5d%5d%5d\n",
		zlm->lxyz[i].Coef,
		zlm->lxyz[i].l[0],
		zlm->lxyz[i].l[1],
		zlm->lxyz[i].l[2]
		);
}
