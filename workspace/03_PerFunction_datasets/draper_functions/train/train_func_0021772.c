ConcreteConfigure(const ProcessingConfig& c)
{
	CopyAsConcreteConfig(mConfig, c);
	int nControls=mConfig.GetNumControls();


	mInArray.Resize(nControls, "array_control", this, &Control2Data::EnqueueControl);


	BufferQueueInit( nControls );

	mStop.DoControl(0);

	return true;

}
