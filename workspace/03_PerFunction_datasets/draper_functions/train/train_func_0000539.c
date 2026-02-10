suspend(bool force) const
	{
		if(!mSystemSession->suspend(force))
			throwError("SuspendError", tr("Suspend failed"));

		return thisObject();
	}
