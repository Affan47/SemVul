CleanUpClientList()
{


	const uint32 cur_tick = ::GetTickCount();
	if (m_dwLastClientCleanUp + CLIENTLIST_CLEANUP_TIME < cur_tick ){
		m_dwLastClientCleanUp = cur_tick;
		DEBUG_ONLY( uint32 cDeleted = 0; )
		IDMap::iterator current_it = m_clientList.begin();
		while (current_it != m_clientList.end()) {
			CUpDownClient* pCurClient = current_it->second.GetClient();
			++current_it;


			if (pCurClient->GetSourceFrom() == SF_SOURCE_SEEDS && cur_tick - (uint32)theStats::GetStartTime() < MIN2MS(10)) continue;
			if ((pCurClient->GetUploadState() == US_NONE || (pCurClient->GetUploadState() == US_BANNED && !pCurClient->IsBanned()))
				&& pCurClient->GetDownloadState() == DS_NONE
				&& pCurClient->GetChatState() == MS_NONE
				&& pCurClient->GetKadState() == KS_NONE
				&& pCurClient->GetSocket() == NULL)
			{
				DEBUG_ONLY( cDeleted++; )
				pCurClient->Disconnected(wxT("Removed during ClientList cleanup."));
				pCurClient->Safe_Delete();
#ifdef __DEBUG__
			} else {
				if (!(pCurClient->GetUploadState() == US_NONE || (pCurClient->GetUploadState() == US_BANNED && !pCurClient->IsBanned()))) {
					AddDebugLogLineN(logProxy,
						CFormat(wxT("Debug: Not deleted client %x with up state: %i "))
							% (long int)pCurClient % pCurClient->GetUploadState());
				}
				if (!(pCurClient->GetDownloadState() == DS_NONE)) {
					AddDebugLogLineN(logProxy,
						CFormat(wxT("Debug: Not deleted client %x with down state: %i "))
							% (long int)pCurClient % pCurClient->GetDownloadState());
				}
				if (!(pCurClient->GetChatState() == MS_NONE)) {
					AddDebugLogLineN(logProxy,
						CFormat(wxT("Debug: Not deleted client %x with chat state: %i "))
							% (long int)pCurClient % pCurClient->GetChatState());
				}
				if (!(pCurClient->GetKadState() == KS_NONE)) {
					AddDebugLogLineN(logProxy,
						CFormat(wxT("Debug: Not deleted client %x with kad state: %i ip: %s"))
							% (long int)pCurClient % (int)pCurClient->GetKadState() % pCurClient->GetFullIP());
				}
				if (!(pCurClient->GetSocket() == NULL)) {
					AddDebugLogLineN(logProxy,
						CFormat(wxT("Debug: Not deleted client %x: has socket")) % (long int)pCurClient);
				}
				AddDebugLogLineN(logProxy,
					CFormat(wxT("Debug: Not deleted client %x with kad version: %i"))
						% (long int)pCurClient % pCurClient->GetKadVersion());
#endif
			}
		}
		AddDebugLogLineN(logClient, CFormat(wxT("Cleaned ClientList, removed %i not used known clients")) % cDeleted);
	}
}
