loop()
	{

		CASingleSocketGroup oSocketGroup(false);
		oSocketGroup.add(*m_pMuxIn);
		m_pMuxIn->setCrypt(true);
		m_pMuxOut->setCrypt(true);

		m_bRun=true;

		CAThread oThread;
		oThread.setMainLoop(mm_loopReadFromMixAfter);
		oThread.start(this);

		CAThread bThread;
		bThread.setMainLoop(mm_loopSendToMixBefore);
		bThread.start(this);

		CAThread cThread;
		cThread.setMainLoop(mm_loopReadFromMixBefore);
		cThread.start(this);

		CAThread dThread;
		dThread.setMainLoop(mm_loopSendToMixAfter);
		dThread.start(this);

		cThread.join();

		CAMsg::printMsg(LOG_CRIT,"loop(): Preparing for restart...\n");
		m_bRun=false;

		oThread.join();
		bThread.join();
		dThread.join();

		m_pMuxIn->close();
		m_pMuxOut->close();

		CAMsg::printMsg(LOG_CRIT,"loop(): Seems that we are restarting now!!\n");
		return E_UNKNOWN;
	}
