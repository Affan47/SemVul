sort_basis_by_sym(OneBasis* Basis,gint nbasis,TypeBasisBySym BasisBySym[MAXSYM])
{
	gint i;
	gint j;
	gint maxsym = 0;
	for(i=0;i<MAXSYM;i++)
	{
		BasisBySym[i].Nbasis = 0;
		BasisBySym[i].Basis = NULL;
	}
	for(j=0;j<nbasis;j++)
	{
		if(Basis[j].numsym>maxsym)
			maxsym = Basis[j].numsym;
		i = Basis[j].numsym-1;
		BasisBySym[i].Nbasis++;
		if(!BasisBySym[i].Basis)
			BasisBySym[i].Basis = g_malloc(sizeof(OneBasis));
		else
			BasisBySym[i].Basis = g_realloc(BasisBySym[i].Basis,BasisBySym[i].Nbasis*sizeof(OneBasis));
		BasisBySym[i].Basis[BasisBySym[i].Nbasis-1] = Basis[j];
	}
	return maxsym;


}
