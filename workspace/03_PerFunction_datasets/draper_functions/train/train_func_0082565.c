reportProgress(size_t bytesCompleted,
					      size_t bytesEstimatedTotal,

					      size_t messagesCompleted,
					      size_t messagesEstimatedTotal)
{
	if (callbackPtr)
		callbackPtr->
			reportProgress(bytesCompleted, bytesEstimatedTotal,
				       messagesCompleted,
				       messagesEstimatedTotal);
}
