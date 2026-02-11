vectorize (header *init, header *step, header *end)
{	double vinit,vstep,vend,*m;
	int count;
	header *result,*st=init;
	init=getvalue(init); step=getvalue(step); end=getvalue(end);
	if (error) return;
	if (init->type!=s_real || step->type!=s_real || end->type!=s_real)
	{	output("The : allows only real arguments!\n");
		error=15; return;
	}
	vinit=*realof(init); vstep=*realof(step); vend=*realof(end);
	if (vstep==0)
	{	output("A step size of 0 is not allowed in : \n");
		error=401; return;
	}
	if (fabs(vend-vinit)/fabs(vstep)+1+epsilon>INT_MAX)
	{	output1("A vector can only have %d elements\n",INT_MAX);
		error=402; return;
	}
	count=(int)(floor(fabs(vend-vinit)/fabs(vstep)+1+epsilon));
	if ((vend>vinit && vstep<0) || (vend<vinit && vstep>0))
		count=0;
	result=new_matrix(1,count,""); if (error) return;
	m=matrixof(result);
	while (count>=0)
	{	*m++=vinit;
		vinit+=vstep;
		count--;
	}
	moveresult(st,result);
}
