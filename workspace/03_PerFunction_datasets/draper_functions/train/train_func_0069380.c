Entry()
	{
		m_sync.Lock();
		for (;;)
		{
			if (!IdleLoop())
			{
				m_finished = true;
				m_sync.Unlock();
				return 0;
			}

			if (m_pSocket->m_state == CSocket::listening)
			{
				while (IdleLoop())
				{
					if (m_pSocket->m_fd == -1)
					{
						m_waiting = 0;
						break;
					}
					if (!DoWait(0))
						break;
					SendEvents();
				}
			}
			else
			{
				if (m_pSocket->m_state == CSocket::connecting)
				{
					if (!DoConnect())
						continue;
				}

#ifdef __WXMSW__
				m_waiting |= WAIT_CLOSE;
				int wait_close = WAIT_CLOSE;
#endif
				while (IdleLoop())
				{
					if (m_pSocket->m_fd == -1)
					{
						m_waiting = 0;
						break;
					}
					bool res = DoWait(0);

					if (m_triggered & WAIT_CLOSE && m_pSocket)
					{
						m_pSocket->m_state = CSocket::closing;
#ifdef __WXMSW__
						wait_close = 0;
#endif
					}

					if (!res)
						break;

					SendEvents();
#ifdef __WXMSW__
					m_waiting |= wait_close;
#endif
				}
			}
		}

		m_finished = true;
		return 0;
	}
