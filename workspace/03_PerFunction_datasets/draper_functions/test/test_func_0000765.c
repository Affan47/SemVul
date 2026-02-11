mtype (header *hd)
{	header *st=hd,*result;
	hd=getvalue(hd); if (error) return;
	result=new_real(hd->type,"");
	moveresult(st,result);
}
