Do()
{
	if( !AbleToExecute() ) return true;

	CLAM::TData newValue = sin(mPhase);
	mPhase += mDeltaPhase;
	if (mPhase > (2*M_PI))
	{
		mPhase = fmod(mPhase,TData(2*M_PI));
	}

	CLAM::TData firstValue = fabs(newValue);
	CLAM::TData secondValue = 1 - fabs(newValue);

	mLeft.SendControl(firstValue);
	mRight.SendControl(secondValue);
       	return true;
}
