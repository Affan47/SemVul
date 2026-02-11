clean()
	{
		emit hideProgressDialog();

		mProgressTimer.stop();

		mDeviceCopyThread->stop();
		mDeviceCopyThread->wait();
		delete mDeviceCopyThread;

		mInput->close();
		mOutput->close();
	}
