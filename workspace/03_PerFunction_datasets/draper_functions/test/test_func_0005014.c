ResumeFile()
{
	if ( status == PS_COMPLETE || status == PS_COMPLETING ) {
		return;
	}

	if ( m_insufficient && !CheckFreeDiskSpace() ) {

		return;
	}

	m_paused = false;
	m_stopped = false;
	m_insufficient = false;

	m_lastsearchtime = 0;
	SetStatus(status);
	SetActive(theApp->IsConnected());

	if (m_gaplist.IsComplete() && (GetStatus() == PS_ERROR)) {

		CompleteFile(true);
	}

	UpdateDisplayedInfo(true);
}
