CancelLoading()
	{
		if (cancelLoadingCallback) return (*cancelLoadingCallback)();
		return false;
	}
}
