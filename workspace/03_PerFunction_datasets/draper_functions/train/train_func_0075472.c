Do( TData& out )
{
	if( !AbleToExecute() ) return true;

	ApplyFreqAndAmpControls();

	out = mAmp * TData(sin(mPhase));
	mPhase += mDeltaPhase*mSamplesBetweenCallsCtl.GetLastValue();

	if (mPhase>TData(2*PI))
		mPhase-=TData(2*PI);

	return true;
}
