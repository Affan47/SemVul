xfit_del(xfit *p) {
	if (p->v != NULL)
		free(p->v);
	if (p->wv != NULL)
		free(p->wv);
	if (p->sa != NULL)
		free(p->sa);
	if (p->rpoints != NULL)
		free(p->rpoints);
	if (p->piv != NULL)
		free(p->piv);
	if (p->uerrv != NULL)
		free(p->uerrv);
	free(p);
}
