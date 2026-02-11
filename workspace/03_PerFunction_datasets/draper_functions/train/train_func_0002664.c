reportProgress(size_t bytesCompleted,
					     size_t bytesEstimatedTotal,

					     size_t messagesCompleted,
					     size_t messagesEstimatedTotal)
{
	if (me.currentProgressReporter)
		me.currentProgressReporter->operator()
			(bytesCompleted, bytesEstimatedTotal,
			 messagesCompleted,
			 messagesEstimatedTotal);
}
