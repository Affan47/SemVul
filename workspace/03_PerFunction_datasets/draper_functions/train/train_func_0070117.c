getColors(unsigned num)
{

#if 0
	wxCHECK(num < 15, *wxBLACK);
#else

	wxCHECK(num < (15+1), *wxBLACK);
#endif


	return acrStat[num];
}
