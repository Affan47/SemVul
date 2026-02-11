mkeepsquare (header *hd)
{	header *st=hd,*result;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_real)
	{	output("Keepsquare needs a 1 or 0!\n");
		error=2201; return;
	}
	result=new_real(keepsquare,"");
	keepsquare=(*realof(hd)!=0.0);
	moveresult(st,result);
}
