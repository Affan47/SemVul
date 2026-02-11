Do(const Spectrum& in, Spectrum& out)
{
	out = in;

	DataArray& oMag = out.GetMagBuffer();
	const DataArray& iMag = in.GetMagBuffer();

	int spectrumSize = in.GetSize();

	TData spectralResolution = spectrumSize/in.GetSpectralRange();

	int lowCutoff = Round(mLowCutoffFreqCtl.GetLastValue()* spectralResolution);
	int highCutoff = 	Round(mHighCutoffFreqCtl.GetLastValue()* spectralResolution);


	TData lowThreshold = 	log2lin(mLowThresholdCtl.GetLastValue());
	TData midThreshold = 	log2lin(mMidThresholdCtl.GetLastValue());
	TData highThreshold = 	log2lin(mHighThresholdCtl.GetLastValue());

	TData currentThreshold = lowThreshold;
	for(int i = 0; i<lowCutoff; i++)
	{
		if(iMag[i]>lowThreshold)
			oMag[i] = lowThreshold;
	}
	for(int i = lowCutoff; i<highCutoff; i++)
	{
		if(iMag[i]>midThreshold)
			oMag[i] = midThreshold;
	}
	for(int i = highCutoff; i<spectrumSize; i++)
	{
		if(iMag[i]>highThreshold)
			oMag[i] = highThreshold;
	}
	return true;
}
