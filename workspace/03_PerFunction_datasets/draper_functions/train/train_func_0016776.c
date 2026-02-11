start()
	{
		m_pThread=new CAThread();
		m_bRun=true;
		m_pThread->setMainLoop(db_loopMaintenance);
		return m_pThread->start(this);
	}
