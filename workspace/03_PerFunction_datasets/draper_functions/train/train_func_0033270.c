OnTerminate(int pid, int status)
		{
			m_pid = pid;
			m_status = status;

			if( m_waitdlg ) {

				m_waitdlg->EndModal(wxID_OK);
			}
			else {

				delete this;
			}
		}
