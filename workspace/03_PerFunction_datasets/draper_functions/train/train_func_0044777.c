Do(const SpectralPeakArray& inPeaks,
				const Fundamental& inFund,
				const Spectrum& inSpectrum,
				SpectralPeakArray& outPeaks,
				Fundamental& outFund,
				Spectrum& outSpectrum)
{


	if(!inFund.GetFreq(0))
	{
		outFund = inFund;
		outSpectrum = inSpectrum;
		outPeaks = inPeaks;
		return true;
	}
	TData minPitch = 100;
	TData maxPitch = 800;


	TData maxSss = 200;


	TData sssAmount;

	TData pitch = inFund.GetFreq(0);

	if(pitch<minPitch) sssAmount = 0;
	else if (pitch>maxPitch) sssAmount = maxSss;
	else sssAmount = (pitch-minPitch) / ( (maxPitch-minPitch)/maxSss);
	TData pitchTransposition=2;

	bool femaleToMale = mControl.GetLastValue()>0;
	if(femaleToMale)
	{

		sssAmount = -sssAmount;
		pitchTransposition=1/pitchTransposition;
	}

	SendFloatToInControl(mSpectralShapeShift,"Shift Steps",sssAmount);
	SendFloatToInControl(mPitchShift,"PitchSteps",pitchTransposition);

	SpectralPeakArray tmpSpectralPeaks;
	mSpectralShapeShift.Do(inPeaks,tmpSpectralPeaks);
	mPitchShift.Do( tmpSpectralPeaks, inFund, inSpectrum,
			outPeaks, outFund, outSpectrum);
	return true;
}
