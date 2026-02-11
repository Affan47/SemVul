ScaKwdHdr(GmfMshSct *msh, int KwdCod)
{
	int i;
	KwdSct *kwd = &msh->KwdTab[ KwdCod ];

	if(!strcmp("i", KwdFmt[ KwdCod ][1]))
	{
		if(msh->typ & Asc)
			fscanf(msh->hdl, "%d", &kwd->NmbLin);
		else
			ScaWrd(msh, (unsigned char *)&kwd->NmbLin);
	}
	else
		kwd->NmbLin = 1;

	if(!strcmp("sr", KwdFmt[ KwdCod ][2]))
	{
		if(msh->typ & Asc)
		{
			fscanf(msh->hdl, "%d", &kwd->NmbTyp);

			for(i=0;i<kwd->NmbTyp;i++)
				fscanf(msh->hdl, "%d", &kwd->TypTab[i]);
		}
		else
		{
			ScaWrd(msh, (unsigned char *)&kwd->NmbTyp);

			for(i=0;i<kwd->NmbTyp;i++)
				ScaWrd(msh, (unsigned char *)&kwd->TypTab[i]);
		}
	}

	ExpFmt(msh, KwdCod);
	kwd->pos = ftell(msh->hdl);
}
