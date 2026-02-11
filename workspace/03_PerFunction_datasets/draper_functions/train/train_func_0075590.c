Do( const Audio& pitchModIn, const int& dum, Audio& out )
{
	if( !AbleToExecute() ) return true;

	ApplyControls();

	TData* ptr = out.GetBuffer().GetPtr();
	TData* pitchModptr = pitchModIn.GetBuffer().GetPtr();

	for (int i=0;i<out.GetSize();i++)
	{
		(*ptr++) = mAmp * TData(sin(mPhase));
		mPhase += mDeltaPhase*(*pitchModptr++);

		if (mPhase>TData(2.*PI) )
			mPhase-=TData(2.*PI);

		if (mPhase<0)
			mPhase+=TData(2.*PI);
	}
	return true;
}
