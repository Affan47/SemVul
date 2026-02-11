ViewerCleanup ()
{
	mViewerReady = false;

        g_free (mViewerBusAddress);
        mViewerBusAddress = NULL;
        g_free (mViewerServiceName);
        mViewerServiceName = NULL;

	if (mBusWatchId) {
		g_bus_unwatch_name (mBusWatchId);
		mBusWatchId = 0;
	}

	if (mCancellable) {
		g_cancellable_cancel (mCancellable);
		g_object_unref (mCancellable);
		mCancellable = NULL;
	}

	if (mViewerProxy) {
		g_signal_handler_disconnect (mViewerProxy, mSignalId);
		mSignalId = 0;

		g_object_unref (mViewerProxy);
		mViewerProxy = NULL;
	}

	if (mViewerFD >= 0) {
		close (mViewerFD);
		mViewerFD = -1;
	}

	if (mViewerPID) {
		kill (mViewerPID, SIGKILL);
		g_spawn_close_pid (mViewerPID);
		mViewerPID = 0;
	}
}
