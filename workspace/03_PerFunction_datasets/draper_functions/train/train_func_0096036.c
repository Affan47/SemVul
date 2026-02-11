checkStatus()
{


	if (!isBufferDependent()) {
		updateView();
		return;
	}


	if (!isBufferAvailable()) {
		enableView(false);
		return;
	}


	if (canApply()) {
		bool const readonly = isBufferReadonly();
		enableView(!readonly || canApplyToReadOnly());


		updateView();
	} else
		enableView(false);
}
