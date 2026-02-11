latticeMSVector(double *Mh, double *yk)
{


	if((!Mh)||(!yk))
	{
		ErrorHandler("MeanShift", "lmsVector", "Invalid argument(s) passed to this method.");
		return;
	}


	classConsistencyCheck(N+2, true);


	LatticeMSVector(Mh, yk);


	return;

}
