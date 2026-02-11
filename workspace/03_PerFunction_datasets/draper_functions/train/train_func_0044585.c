UpdateAutoUpPriority()
{

	uint8 priority = PR_NORMAL;

	if (!IsAutoUpPriority())
		priority = GetUpPriority();

	if ( priority == PR_POWERSHARE && m_nCompleteSourcesCount > 10)
		priority = PR_VERYHIGH;


	if (IsAutoUpPriority()) {
		uint32 queued = GetQueuedCount();

#if 0
		uint8 priority = PR_NORMAL;

		if (queued > 20) {
#else
		if ( m_nCompleteSourcesCount > 0 && m_nCompleteSourcesCount < 8 ) {
			priority = PR_VERYHIGH;
		} else if (queued > 20) {
#endif

			priority = PR_LOW;
		} else if (queued > 1) {
			priority = PR_NORMAL;
		} else {
			priority = PR_HIGH;
		}

	}


		if (GetUpPriority() != priority) {
			SetUpPriority(priority, false);
			Notify_SharedFilesUpdateItem(this);

#if 0
		}
#endif

	}
}
