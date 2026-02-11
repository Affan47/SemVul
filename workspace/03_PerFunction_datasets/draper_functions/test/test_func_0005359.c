msVector(double *Mh, double *yk)
{


	if((!Mh)||(!yk))
	{
		ErrorHandler("MeanShift", "msVector", "Invalid argument(s) passed to this method.");
		return;
	}


	classConsistencyCheck(N, false);


	MSVector(Mh, yk);


	return;

}
