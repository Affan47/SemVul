footprint(u_short a, u_short b, int c, int d)
{
    fp[fp_next].time=time(NULL);
    fp[fp_next].a=a;
    fp[fp_next].b=b;
    fp[fp_next].c=c;
    fp[fp_next].d=d;
    if (fp_next++ >= fp_num)
	fp_next=0;
}
