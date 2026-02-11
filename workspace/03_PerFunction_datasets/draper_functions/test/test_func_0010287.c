mfillcolor (header *hd)
{   header *st=hd,*res;
	int o1=fillcolor1,o2=fillcolor2;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_matrix || dimsof(hd)->r!=1 || dimsof(hd)->c!=2)
	{	output("Argument for fillcolor must be a 1x2 vector!\n");
		error=90; return;
	}
	fillcolor1=(int)*matrixof(hd);
	fillcolor2=(int)*(matrixof(hd)+1);
	if (fillcolor1<0 || fillcolor1>15) fillcolor1=0;
	if (fillcolor2<0 || fillcolor2>15) fillcolor2=0;
	res=new_matrix(1,2,""); if (error) return;
	*matrixof(res)=o1; *(matrixof(res)+1)=o2;
	moveresult(st,res);
}
