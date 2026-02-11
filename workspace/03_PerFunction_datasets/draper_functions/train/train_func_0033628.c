SaveSourceSeeds()
{
	#define MAX_SAVED_SOURCES 10


	if (GetSourceCount()>20) {
		return;
	}

	CClientRefList source_seeds;
	int n_sources = 0;

	CClientRefList::iterator it = m_downloadingSourcesList.begin();
	for( ; it != m_downloadingSourcesList.end() && n_sources < MAX_SAVED_SOURCES; ++it) {


		CClientRef safety(*it);

		if (!it->HasLowID()) {
			source_seeds.push_back(*it);
			++n_sources;
		}
	}

	if (n_sources < MAX_SAVED_SOURCES) {

		if (GetSourceCount() > 0) {
			SourceSet::reverse_iterator rit = m_SrcList.rbegin();
			for ( ; ((rit != m_SrcList.rend()) && (n_sources<MAX_SAVED_SOURCES)); ++rit) {
				if (!rit->HasLowID()) {
					source_seeds.push_back(*rit);
					++n_sources;
				}
			}
		}
	}


	if (!n_sources) {
		return;
	}

	const CPath seedsPath = m_fullname.AppendExt(wxT(".seeds"));

	CFile file;
	file.Create(seedsPath, true);
	if (!file.IsOpened()) {
		AddLogLineN(CFormat( _("Failed to save part.met.seeds file for %s") )
			% m_fullname);
		return;
	}

	try {
		file.WriteUInt8(0);
		file.WriteUInt8(source_seeds.size());

		CClientRefList::iterator it2 = source_seeds.begin();
		for (; it2 != source_seeds.end(); ++it2) {
			CUpDownClient* cur_src = it2->GetClient();
			file.WriteUInt32(cur_src->GetUserIDHybrid());
			file.WriteUInt16(cur_src->GetUserPort());
			file.WriteHash(cur_src->GetUserHash());

			const uint8 uSupportsCryptLayer	= cur_src->SupportsCryptLayer() ? 1 : 0;
			const uint8 uRequestsCryptLayer	= cur_src->RequestsCryptLayer() ? 1 : 0;
			const uint8 uRequiresCryptLayer	= cur_src->RequiresCryptLayer() ? 1 : 0;
			const uint8 byCryptOptions = (uRequiresCryptLayer << 2) | (uRequestsCryptLayer << 1) | (uSupportsCryptLayer << 0);
			file.WriteUInt8(byCryptOptions);
		}


		file.WriteUInt32(wxDateTime::Now().GetTicks());

		AddLogLineN(CFormat( wxPLURAL("Saved %i source seed for partfile: %s (%s)", "Saved %i source seeds for partfile: %s (%s)", n_sources) )
			% n_sources
			% m_fullname
			% GetFileName());
	} catch (const CIOFailureException& e) {
		AddDebugLogLineC( logPartFile, CFormat( wxT("Error saving partfile's seeds file (%s - %s): %s") )
				% m_partmetfilename
				% GetFileName()
				% e.what() );

		n_sources = 0;
		file.Close();
		CPath::RemoveFile(seedsPath);
	}
}
