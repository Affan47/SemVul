mholding (header *hd)
{	header *st=hd,*result;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_real)
	{	output("Holding needs a 1 or 0!\n");
		error=2201; return;
	}
	result=new_real(holding,"");
	holding=(*realof(hd)!=0.0); scaling=!holding;
	moveresult(st,result);
}
