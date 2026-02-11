copyZlm(Zlm* zlm, Zlm* right)
{
	gint i;
	if(zlm == right) return;

	destroyZlm(zlm);
	zlm->l = right->l;
	zlm->m = right->m;
	zlm->numberOfCoefficients = right->numberOfCoefficients;
	zlm->lxyz = g_malloc(zlm->numberOfCoefficients*sizeof(LXYZ));
	for(i=0; i<zlm->numberOfCoefficients; i++)
		zlm->lxyz[i] = right->lxyz[i];
}
