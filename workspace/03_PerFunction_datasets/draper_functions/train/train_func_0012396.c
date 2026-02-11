Tracking(const SpectralPeakArray& iPeakArray,SpectralPeakArray& oPeakArray,TIndex processedPeakPos) const
{
	const DataArray & previousFreqBuffer = mPreviousPeakArray.GetFreqBuffer();
	const IndexArray & previousIndexBuffer = mPreviousPeakArray.GetIndexArray();
	TData currentPeakFreq = previousFreqBuffer[processedPeakPos];

	const DataArray& iFreqBuffer=iPeakArray.GetFreqBuffer();

	if(!ThereIsCandidate(currentPeakFreq,iPeakArray,oPeakArray))
	{
		KillTrack(previousIndexBuffer[processedPeakPos]);
		return;
	}

	TData distance;
	int candidatePos=GetCandidate(currentPeakFreq,iPeakArray,distance);
	if(candidatePos==-1) return;
	TData candidatePeakFreq = iFreqBuffer[candidatePos];

	if( candidatePos>=oPeakArray.GetnPeaks()
	    || (!IsBestCandidate(candidatePeakFreq,currentPeakFreq))
	    || (oPeakArray.GetIndex(candidatePos)!=-1) )
	{
		KillTrack(previousIndexBuffer[processedPeakPos]);
		return;
	}


	const SpectralPeak candidatePeak = iPeakArray.GetSpectralPeak(candidatePos);
	TIndex trackId = previousIndexBuffer[processedPeakPos];
	oPeakArray.SetSpectralPeak(candidatePos,candidatePeak,trackId);
}
