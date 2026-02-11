setRegs(Views v, bool view)
{
	if (view)
		mView |= v;
	else
		mView &= 255-v;
	std::stringstream ss;
	ss << mView;
	mPrefs[RegsViews] = ss.str();
	write();
}
