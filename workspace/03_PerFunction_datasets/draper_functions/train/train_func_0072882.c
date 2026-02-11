mchar (header *hd)
{	header *st=hd,*result;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_real) wrong_arg_in("char");
	result=new_string("a",1,""); if (error) return;
	*stringof(result)=(char)*realof(hd);
	moveresult(st,result);
}
