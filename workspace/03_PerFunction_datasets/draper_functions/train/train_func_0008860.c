Do(const Spectrum& in, Spectrum& out)
{
	if ( !mConfig.GetPreserveOuts() )
	{
		out = in;
	}

	DataArray& oMag = out.GetMagBuffer();

	int spectrumSize = in.GetSize();

	TData spectralResolution = spectrumSize/in.GetSpectralRange();

	int lowCutoff = Round(mLowCutoffFreqCtl.GetLastValue()* spectralResolution);
	int highCutoff = Round(mHighCutoffFreqCtl.GetLastValue()* spectralResolution);


	TData lowGain = 	log2lin(mLowGainCtl.GetLastValue());
	TData midGain = 	log2lin(mMidGainCtl.GetLastValue());
	TData highGain = 	log2lin(mHighGainCtl.GetLastValue());

	TData currentGain = lowGain;
	for(int i = 0; i<spectrumSize; i++)
	{
		if(i>highCutoff)
			currentGain = highGain;
		else if(i==highCutoff)
			currentGain = (highGain+midGain)*0.5;
		else if(i>lowCutoff)
			currentGain = midGain;
		else if(i==lowCutoff)
			currentGain = (lowGain+midGain)*0.5;
		oMag[i] *= currentGain;
	}
	return true;
}


}
