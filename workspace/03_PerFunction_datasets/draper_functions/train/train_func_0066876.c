spread1i (double f (double),
	void fc (double *, double *, double *, double *),
	void fi (double *, double *, double *, double *),
	header *hd)
{	header *result,*st=hd;
	hd=getvalue(hd);
	if (error) return;
	func=f;
	if (isinterval(hd)) result=map1i(fi,hd);
	else result=map1(funceval,fc,hd);
	if (!error) moveresult(st,result);
}
