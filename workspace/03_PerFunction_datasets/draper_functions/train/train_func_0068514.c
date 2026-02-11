load(int i, double res)
{

	operator[](i) = res;

	int t = aa.order[i];
	if (t >= 0)
		etree.set_nulary(t, res);
}
