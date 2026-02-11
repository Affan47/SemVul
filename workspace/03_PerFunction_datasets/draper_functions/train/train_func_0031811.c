Do(const SpectralPeakArray& iPeakArray,SpectralPeakArray& oPeakArray)
{

	oPeakArray.AddIndexArray();
	oPeakArray.AddPhaseBuffer();
	oPeakArray.AddBinWidthBuffer();
	oPeakArray.AddBinPosBuffer();
	oPeakArray.UpdateData();

	TData fn = mFundFreqValue.GetLastValue();
	if(mHarmonic && fn>0)
	{
		mLastHarmonic=true;
		return DoHarmonic(iPeakArray,oPeakArray,fn);
	}
	else
	{
		if(mLastHarmonic) KillAll();
		mLastHarmonic=false;
		return DoInharmonic(iPeakArray,oPeakArray);
	}
}
