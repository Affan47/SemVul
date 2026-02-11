IsFiltered(uint32 IPTest, bool isServer)
{
	if ((!thePrefs::IsFilteringClients() && !isServer) || (!thePrefs::IsFilteringServers() && isServer)) {
		return false;
	}
	if (!m_ready) {


		AddDebugLogLineN(logIPFilter, CFormat(wxT("Filtered IP %s because filter isn't ready yet.")) % Uint32toStringIP(IPTest));
		if (isServer) {
			theStats::AddFilteredServer();
		} else {
			theStats::AddFilteredClient();
		}
		return true;
	}
	wxMutexLocker lock(m_mutex);

	uint32 ip = wxUINT32_SWAP_ALWAYS(IPTest);
	int imin = 0;
	int imax = m_rangeIPs.size() - 1;
	int i;
	bool found = false;
	while (imin <= imax) {
		i = (imin + imax) / 2;
		uint32 curIP = m_rangeIPs[i];
		if (curIP <= ip) {
			uint32 curLength = m_rangeLengths[i];
			if (curLength >= 0x8000) {
				curLength = ((curLength & 0x7fff) << 12) + 0xfff;
			}
			if (curIP + curLength >= ip) {
				found = true;
				break;
			}
		}
		if (curIP > ip) {
			imax = i - 1;
		} else {
			imin = i + 1;
		}
	}
	if (found) {
		AddDebugLogLineN(logIPFilter, CFormat(wxT("Filtered IP %s%s")) % Uint32toStringIP(IPTest)
			% (i < (int)m_rangeNames.size() ? (wxT(" (") + wxString(char2unicode(m_rangeNames[i].c_str())) + wxT(")"))
											: wxString(wxEmptyString)));
		if (isServer) {
			theStats::AddFilteredServer();
		} else {
			theStats::AddFilteredClient();
		}
		return true;
	}
	return false;
}
