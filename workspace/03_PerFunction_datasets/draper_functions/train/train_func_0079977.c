SendNextCommand()
{
	switch (m_state)
	{
	case 1:
		if (!Send(_T("USER ") + wxString(PACKAGE_NAME, wxConvLocal)))
			return;
		break;
	case 2:
		if (!Send(_T("PASS ") + wxString(PACKAGE_VERSION, wxConvLocal)))
			return;
		break;
	case 3:
		{
			PrintMessage(_("Checking for correct external IP address"), 0);
			wxString ip = GetExternalIPAddress();
			if (ip == _T(""))
				return;
			if (!GetIPV6LongForm(ip).IsEmpty())
			{
				PrintMessage(_("You appear to be using an IPv6-only host. This wizard does not support this environment."), 1);
				CloseSocket();
				return;
			}
			m_externalIP = ip;

			wxString hexIP = ip;
			for (unsigned int i = 0; i < hexIP.Length(); i++)
			{
				wxChar& c = hexIP[i];
				if (c == '.')
					c = '-';
				else
					c = c - '0' + 'a';
			}

			if (!Send(_T("IP ") + ip + _T(" ") + hexIP))
				return;

		}
		break;
	case 4:
		{
			int port = CreateListenSocket();
			if (!port)
			{
				PrintMessage(_("Failed to create listen socket, aborting"), 1);
				CloseSocket();
				return;
			}
			m_listenPort = port;
			Send(wxString::Format(_T("PREP %d"), port));
			break;
		}
	case 5:
		{
			wxString cmd = wxString::Format(_T("PORT %s,%d,%d"), m_externalIP.c_str(), m_listenPort / 256, m_listenPort % 256);
			cmd.Replace(_T("."), _T(","));
			Send(cmd);
		}
		break;
	case 6:
		Send(_T("LIST"));
		break;
	case 7:
		m_testResult = successful;
		Send(_T("QUIT"));
		break;
	case 8:
		CloseSocket();
		break;
	}
}
