powerOff()
{
	if (!mHerculesActive) return ;
	mMinimizeOnClose=false;
	printf("Goodbye!\n");
	mHerculesExecutor->issueCommand("quit\n");
	#ifndef hFramework
	usleep(100000);
	#endif
	mDevicesPane->clear();

	mPsw->setDormant();
    mCommandLine->save();
}
