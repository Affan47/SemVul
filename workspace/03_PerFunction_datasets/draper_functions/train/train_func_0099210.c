invert (header *hd)


{	header *result,*st=hd;
	hd=getvalue(hd);
	if (error) return;
	if (isinterval(hd))
		result=map1i(interval_invert,hd);
	else result=map1(real_invert,complex_invert,hd);
	if (!error) moveresult(st,result);
}
