Do( const MelSpectrum& melSpec, MelCepstrum& melCeps )
{
	if ( !AbleToExecute() ) return false;

	const DataArray& melCoeffs = melSpec.GetCoefficients();
	DataArray&  cepstrumCoeffs = melCeps.GetCoefficients();
	const TSize numMelCoefficients = melCoeffs.Size();
	const TSize numCepstrumCoeffs  = mConfig.GetNumCepstrumCoefficients();

	if ( cepstrumCoeffs.Size() < numCepstrumCoeffs )
	{
		cepstrumCoeffs.Resize(numCepstrumCoeffs);
		cepstrumCoeffs.SetSize(numCepstrumCoeffs);
	}

	melCeps.SetCenterTime(melSpec.GetCenterTime());
	melCeps.SetLowCutoff(melSpec.GetLowCutoff());
	melCeps.SetHighCutoff(melSpec.GetHighCutoff());


	const TData melFloor  = 1.0;
	const bool  useBase10 = mConfig.GetUseBase10();

	if ( mLogBuffer.Size()!=numMelCoefficients)
	{

		mLogBuffer.Resize(numMelCoefficients);
		mLogBuffer.SetSize(numMelCoefficients);
	}
	for (TIndex i=0; i<numMelCoefficients; i++) {
		if (melCoeffs[i] < melFloor)
			mLogBuffer[i] = useBase10 ? log10(melFloor) : log(melFloor);
		else
			mLogBuffer[i] = useBase10 ? log10(melCoeffs[i]) : log(melCoeffs[i]);
	}


	const TData piord = PI / (TData)numMelCoefficients;
	const TData scale = sqrt(2.0/(TData)numMelCoefficients);


	TData freq = 0;
	for (TIndex i=1; i<numCepstrumCoeffs; i++)
	{
		freq = i*piord;
		cepstrumCoeffs[i] = 0.0;
		for (TIndex j=0; j<numMelCoefficients; j++)
			cepstrumCoeffs[i] += mLogBuffer[j] * cos(freq*(j+1 - 0.5));
		cepstrumCoeffs[i] *= scale;
	}


	for (TIndex j=0; j<numMelCoefficients; j++)
		cepstrumCoeffs[0] += mLogBuffer[j];
	cepstrumCoeffs[0] *= scale;


	return true;
}

}
