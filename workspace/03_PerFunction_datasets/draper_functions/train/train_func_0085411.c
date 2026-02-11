shareedge(const int3 &a,const int3 &b)
{
	int i;
	for(i=0;i<3;i++)
	{
		int i1= (i+1)%3;
		if(hasedge(a,b[i1],b[i])) return 1;
	}
	return 0;
}
