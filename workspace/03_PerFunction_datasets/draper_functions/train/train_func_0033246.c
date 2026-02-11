Entry() {
		CTimerEvent evt(m_id);

		uint32 lastEvent = GetTickCountFullRes();
		do {

			uint32 now = GetTickCountFullRes();

			sint32 delta = now - lastEvent;
			if (delta > 100 * m_period) {


				delta = 100 * m_period;
				lastEvent = now - delta;
			}


			sint32 timeout = ((m_period < delta) ? 0 : (m_period - delta));


			if (m_sleepSemaphore.WaitTimeout(timeout) == wxSEMA_TIMEOUT) {

				lastEvent += m_period;

				wxPostEvent(m_owner, evt);
			} else {
				break;
			}
		} while (!m_oneShot);

		return NULL;
	}
