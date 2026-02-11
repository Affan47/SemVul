f6_set_f(f6_t *fil, int f)
{
	fil->f = (f<<13) / fil->rate;
	if(fil->f > 1<<13)
		fil->f = 1<<13;
}
